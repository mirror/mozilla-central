/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are Copyright (C) 1998
 * Netscape Communications Corporation.  All Rights Reserved.
 */
#include "nsGenericDOMDataNode.h"
#include "nsGenericHTMLElement.h"
#include "nsIEventListenerManager.h"
#include "nsIDocument.h"
#include "nsXIFConverter.h"
#include "nsSelectionRange.h"
#include "nsISelection.h"
#include "nsCRT.h"
#include "nsIEventStateManager.h"
#include "nsIPrivateDOMEvent.h"
#include "nsISizeOfHandler.h"
#include "nsDOMEvent.h"
#include "nsIDOMScriptObjectFactory.h"
#include "prprf.h"

// XXX share all id's in this dir

NS_DEFINE_IID(kIDOMDataIID, NS_IDOMDATA_IID);
extern void NS_QuoteForHTML(const nsString& aValue, nsString& aResult);

static NS_DEFINE_IID(kIPrivateDOMEventIID, NS_IPRIVATEDOMEVENT_IID);

//----------------------------------------------------------------------

nsGenericDOMDataNode::nsGenericDOMDataNode()
{
  mDocument = nsnull;
  mParent = nsnull;
  mContent = nsnull;
  mScriptObject = nsnull;
  mListenerManager = nsnull;
  mText = nsnull;
  mTextLength = 0;
}

nsGenericDOMDataNode::~nsGenericDOMDataNode()
{
  if (nsnull != mText) {
    delete [] mText;
  }
  NS_IF_RELEASE(mListenerManager);
  // XXX what about mScriptObject? its now safe to GC it...
}

void
nsGenericDOMDataNode::Init(nsIHTMLContent* aOuterContentObject)
{
  NS_ASSERTION((nsnull == mContent) && (nsnull != aOuterContentObject),
               "null ptr");
  mContent = aOuterContentObject;
}

nsresult
nsGenericDOMDataNode::GetNodeValue(nsString& aNodeValue)
{
  aNodeValue.Truncate();
  aNodeValue.Append(mText, mTextLength);
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::SetNodeValue(const nsString& aNodeValue)
{
  PRUnichar* nt = aNodeValue.ToNewUnicode();
  if (nsnull == nt) {
    return NS_ERROR_OUT_OF_MEMORY;
  }
  if (nsnull != mText) {
    delete [] mText;
  }
  mTextLength = aNodeValue.Length();
  mText = nt;

  // Trigger a reflow
  if (nsnull != mDocument) {
    mDocument->ContentChanged(mContent, nsnull);
  }
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::GetParentNode(nsIDOMNode** aParentNode)
{
  if (nsnull != mParent) {
    nsresult res = mParent->QueryInterface(kIDOMNodeIID, (void**)aParentNode);
    NS_ASSERTION(NS_OK == res, "Must be a DOM Node");
    return res;
  }
  else {
    *aParentNode = nsnull;
  }
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::GetPreviousSibling(nsIDOMNode** aNode)
{
  if (nsnull != mParent) {
    PRInt32 pos;
    mParent->IndexOf(mContent, pos);
    if (pos > -1) {
      nsIContent* prev;
      mParent->ChildAt(--pos, prev);
      if (nsnull != prev) {
        nsresult res = prev->QueryInterface(kIDOMNodeIID, (void**)aNode);
        NS_ASSERTION(NS_OK == res, "Must be a DOM Node");
        NS_RELEASE(prev); // balance the AddRef in ChildAt()
        return res;
      }
    }
  }
  *aNode = nsnull;
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::GetNextSibling(nsIDOMNode** aNextSibling)
{
  if (nsnull != mParent) {
    PRInt32 pos;
    mParent->IndexOf(mContent, pos);
    if (pos > -1 ) {
      nsIContent* prev;
      mParent->ChildAt(++pos, prev);
      if (nsnull != prev) {
        nsresult res = prev->QueryInterface(kIDOMNodeIID,(void**)aNextSibling);
        NS_ASSERTION(NS_OK == res, "Must be a DOM Node");
        NS_RELEASE(prev); // balance the AddRef in ChildAt()
        return res;
      }
    }
  }
  *aNextSibling = nsnull;
  return NS_OK;
}

#if 0
nsresult
nsGenericDOMDataNode::Equals(nsIDOMNode* aNode, PRBool aDeep, PRBool* aReturn)
{
  *aReturn = PR_FALSE;
  PRInt32 nt1, nt2;
  GetNodeType(&nt1);
  aNode->GetNodeType(&nt2);
  if (nt1 != nt2) {
    return NS_OK;
  }
  return NS_OK;
}
#endif

//----------------------------------------------------------------------

// Implementation of nsIDOMData

nsresult    
nsGenericDOMDataNode::GetData(nsString& aData)
{
  if (nsnull != mText) {
    aData.SetString(mText, mTextLength);
  }
  return NS_OK;
}

nsresult    
nsGenericDOMDataNode::SetData(const nsString& aData)
{
  if (mText) {
    delete[] mText;
    mText = nsnull;
  }

  mTextLength = aData.Length();
  mText = aData.ToNewUnicode();

  // Notify the document that the text changed
  if (nsnull != mDocument) {
    mDocument->ContentChanged(mContent, nsnull);
  }
  return NS_OK;
}

nsresult    
nsGenericDOMDataNode::GetSize(PRUint32* aSize)
{
  *aSize = mTextLength;
  return NS_OK;
}

// XXX temporary
#define NS_DOM_INDEX_SIZE_ERR NS_ERROR_FAILURE

nsresult    
nsGenericDOMDataNode::Substring(PRUint32 aStart,
                                PRUint32 aCount,
                                nsString& aReturn)
{
  aReturn.Truncate();
  if (nsnull != mText) {
    // XXX add <0 checks if types change
    if (aStart >= PRUint32(mTextLength)) {
      return NS_DOM_INDEX_SIZE_ERR;
    }
    PRUint32 amount = aCount;
    if (aStart + amount > PRUint32(mTextLength)) {
      amount = mTextLength - aStart;
    }
    aReturn.SetString(mText + aStart, amount);
  }
  return NS_OK;
}

nsresult    
nsGenericDOMDataNode::Append(const nsString& aData)
{
  return Replace(mTextLength, 0, aData);
}

nsresult    
nsGenericDOMDataNode::Insert(PRUint32 aOffset, const nsString& aData)
{
  return Replace(aOffset, 0, aData);
}

nsresult    
nsGenericDOMDataNode::Remove(PRUint32 aOffset, PRUint32 aCount)
{
  nsAutoString empty;
  return Replace(aOffset, aCount, empty);
}

nsresult    
nsGenericDOMDataNode::Replace(PRUint32 aOffset, PRUint32 aCount,
                              const nsString& aData)
{
  // sanitize arguments
  if (aOffset > (PRUint32)mTextLength) {
    aOffset = mTextLength;
  }

  // Allocate new buffer
  PRInt32 endOffset = aOffset + aCount;
  if (endOffset > mTextLength) {
    aCount = mTextLength - aOffset;
    endOffset = mTextLength;
  }
  PRInt32 dataLength = aData.Length();
  PRInt32 newLength = mTextLength - aCount + dataLength;
  PRUnichar* to = new PRUnichar[newLength ? newLength : 1];
  if (nsnull == to) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  // Copy over appropriate data
  if (0 != aOffset) {
    nsCRT::memcpy(to, mText, sizeof(PRUnichar) * aOffset);
  }
  if (0 != dataLength) {
    nsCRT::memcpy(to + aOffset, aData.GetUnicode(),
                  sizeof(PRUnichar) * dataLength);
  }
  if (endOffset != mTextLength) {
    nsCRT::memcpy(to + aOffset + dataLength, mText + endOffset,
                  sizeof(PRUnichar) * (mTextLength - endOffset));
  }

  // Switch to new buffer
  if (nsnull != mText) {
    delete [] mText;
  }
  mText = to;
  mTextLength = newLength;

  // Notify the document that the text changed
  if (nsnull != mDocument) {
    mDocument->ContentChanged(mContent, nsnull);
  }

  return NS_OK;
}

//----------------------------------------------------------------------

// nsIScriptObjectOwner implementation

nsresult
nsGenericDOMDataNode::GetScriptObject(nsIScriptContext* aContext,
                                      void** aScriptObject)
{
  nsresult res = NS_OK;
  if (nsnull == mScriptObject) {
    nsIDOMScriptObjectFactory *factory;
    
    res = nsGenericHTMLElement::GetScriptObjectFactory(&factory);
    if (NS_OK != res) {
      return res;
    }
    
    res = factory->NewScriptData(nsIDOMNode::TEXT, aContext, mContent,
                                 mParent, (void**)&mScriptObject);
    NS_RELEASE(factory);
  }
  *aScriptObject = mScriptObject;
  return res;
}

nsresult
nsGenericDOMDataNode::SetScriptObject(void *aScriptObject)
{
  mScriptObject = aScriptObject;
  return NS_OK;
}

//----------------------------------------------------------------------

// nsIDOMEventReceiver implementation

nsresult
nsGenericDOMDataNode::GetListenerManager(nsIEventListenerManager** aResult)
{
  if (nsnull != mListenerManager) {
    NS_ADDREF(mListenerManager);
    *aResult = mListenerManager;
    return NS_OK;
  }
  nsresult rv = NS_NewEventListenerManager(aResult);
  if (NS_OK == rv) {
    mListenerManager = *aResult;
    NS_ADDREF(mListenerManager);
  }
  return rv;
}

nsresult
nsGenericDOMDataNode::GetNewListenerManager(nsIEventListenerManager** aResult)
{
  return NS_NewEventListenerManager(aResult);
} 

nsresult
nsGenericDOMDataNode::AddEventListener(nsIDOMEventListener* aListener,
                                       const nsIID& aIID)
{
  nsIEventListenerManager *manager;

  if (NS_OK == GetListenerManager(&manager)) {
    manager->AddEventListener(aListener, aIID);
    NS_RELEASE(manager);
    return NS_OK;
  }
  return NS_ERROR_FAILURE;
}

nsresult
nsGenericDOMDataNode::RemoveEventListener(nsIDOMEventListener* aListener,
                                          const nsIID& aIID)
{
  if (nsnull != mListenerManager) {
    mListenerManager->RemoveEventListener(aListener, aIID);
    return NS_OK;
  }
  return NS_ERROR_FAILURE;
}

//----------------------------------------------------------------------

// Implementation of nsIContent


nsresult
nsGenericDOMDataNode::BeginConvertToXIF(nsXIFConverter& aConverter) const
{
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::FinishConvertToXIF(nsXIFConverter& aConverter) const
{
  return NS_OK;
}

/**
 * Translate the content object into the (XIF) XML Interchange Format
 * XIF is an intermediate form of the content model, the buffer
 * will then be parsed into any number of formats including HTML, TXT, etc.
 */
nsresult
nsGenericDOMDataNode::ConvertContentToXIF(nsXIFConverter& aConverter) const
{
  const nsIContent* content = mContent;

  if (aConverter.GetUseSelection() == PR_TRUE && mDocument->IsInSelection(content))
  {
    nsISelection* sel;
    mDocument->GetSelection(sel);
    if (sel != nsnull)
    {
      nsSelectionRange* range = sel->GetRange();
      if (range != nsnull)
      {
        nsSelectionPoint* startPoint = range->GetStartPoint();
        nsSelectionPoint* endPoint = range->GetEndPoint();

        nsIContent* startContent = startPoint->GetContent();
        nsIContent* endContent   = endPoint->GetContent();

        PRInt32 startOffset = startPoint->GetOffset();
        PRInt32 endOffset = endPoint->GetOffset();

        nsString  buffer;
        buffer.Append(mText, mTextLength);
        if (startContent == content || endContent == content)
        { 
          // NOTE: ORDER MATTERS!
          // This must go before the Cut
          if (endContent == content)
            buffer.Truncate(endOffset);            
          
          // This must go after the Trunctate
          if (startContent == content)
           buffer.Cut(0,startOffset); 
        }
        aConverter.AddContent(buffer);
        NS_IF_RELEASE(startContent);
        NS_IF_RELEASE(endContent);
      }
    }
    NS_RELEASE(sel);
  }
  else  
  {
    nsString  buffer;
    buffer.Append(mText, mTextLength);
    aConverter.AddContent(buffer);
  }
  return NS_OK;
}

void
nsGenericDOMDataNode::ToCString(nsString& aBuf, PRInt32 aOffset,
                                PRInt32 aLen) const
{
  PRUnichar* cp = mText + aOffset;
  PRUnichar* end = cp + aLen;
  while (cp < end) {
    PRUnichar ch = *cp++;
    if (ch == '\r') {
      aBuf.Append("\\r");
    } else if (ch == '\n') {
      aBuf.Append("\\n");
    } else if (ch == '\t') {
      aBuf.Append("\\t");
    } else if ((ch < ' ') || (ch >= 127)) {
      char buf[10];
      PR_snprintf(buf, sizeof(buf), "\\u%04x", ch);
      aBuf.Append(buf);
    } else {
      aBuf.Append(ch);
    }
  }
}

nsresult
nsGenericDOMDataNode::GetDocument(nsIDocument*& aResult) const
{
  aResult = mDocument;
  NS_IF_ADDREF(mDocument);
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::SetDocument(nsIDocument* aDocument)
{
  mDocument = aDocument;
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::GetParent(nsIContent*& aResult) const
{
  NS_IF_ADDREF(mParent);
  aResult = mParent;
  return NS_OK;;
}

nsresult
nsGenericDOMDataNode::SetParent(nsIContent* aParent)
{
  mParent = aParent;
  return NS_OK;
}

nsresult
nsGenericDOMDataNode::HandleDOMEvent(nsIPresContext& aPresContext,
                                     nsEvent* aEvent,
                                     nsIDOMEvent** aDOMEvent,
                                     PRUint32 aFlags,
                                     nsEventStatus& aEventStatus)
{
  nsresult ret = NS_OK;
  
  nsIDOMEvent* domEvent = nsnull;
  if (DOM_EVENT_INIT == aFlags) {
    nsIEventStateManager *manager;
    if (NS_OK == aPresContext.GetEventStateManager(&manager)) {
      manager->SetEventTarget(mContent);
      NS_RELEASE(manager);
    }
    aDOMEvent = &domEvent;
  }
  
  //Capturing stage
  
  //Local handling stage
  if (nsnull != mListenerManager) {
    mListenerManager->HandleEvent(aPresContext, aEvent, aDOMEvent, aEventStatus);
  }

  //Bubbling stage
  if (DOM_EVENT_CAPTURE != aFlags && mParent != nsnull) {
    ret = mParent->HandleDOMEvent(aPresContext, aEvent, aDOMEvent,
                                  DOM_EVENT_BUBBLE, aEventStatus);
  }

  if (DOM_EVENT_INIT == aFlags) {
    // We're leaving the DOM event loop so if we created a DOM event,
    // release here.
    if (nsnull != *aDOMEvent) {
      if (0 != (*aDOMEvent)->Release()) {
        // Okay, so someone in the DOM loop (a listener, JS object)
        // still has a ref to the DOM Event but the internal data
        // hasn't been malloc'd.  Force a copy of the data here so the
        // DOM Event is still valid.
        nsIPrivateDOMEvent *privateEvent;
        if (NS_OK == (*aDOMEvent)->QueryInterface(kIPrivateDOMEventIID, (void**)&privateEvent)) {
          privateEvent->DuplicatePrivateData();
          NS_RELEASE(privateEvent);
        }
      }
    }
    aDOMEvent = nsnull;
  }
  return ret;
}

//----------------------------------------------------------------------

// Implementation of nsIHTMLContent

nsresult
nsGenericDOMDataNode::Compact()
{
  return NS_OK;
}

// XXX not really implemented (yet)
nsresult
nsGenericDOMDataNode::SizeOf(nsISizeOfHandler* aHandler) const
{
  aHandler->Add(sizeof(*this));
  return NS_OK;
}

