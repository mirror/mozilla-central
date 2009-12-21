/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Private Browsing Tests.
 *
 * The Initial Developer of the Original Code is
 * William Jon McCann
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   William Jon McCann <william.jon.mccann@gmail.com> (Original Author)
 *   Ehsan Akhgari <ehsan.akhgari@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

// This test checks the browser -private command line option.

function testprivatecl() {
}

testprivatecl.prototype = {
  _arguments: ["private", "silent"],
  get length getLength() {
    return this._arguments.length;
  },
  getArgument: function getArgument(aIndex) {
    return this._arguments[aIndex];
  },
  findFlag: function findFlag(aFlag, aCaseSensitive) {
    for (let i = 0; i < this._arguments.length; ++i)
      if (aCaseSensitive ?
          (this._arguments[i] == aFlag) :
          (this._arguments[i].toLowerCase() == aFlag.toLowerCase()))
        return i;
    return -1;
  },
  removeArguments: function removeArguments(aStart, aEnd) {
    this._arguments.splice(aStart, aEnd - aStart + 1);
  },
  handleFlag: function handleFlag (aFlag, aCaseSensitive) {
    let res = this.findFlag(aFlag, aCaseSensitive);
    if (res > -1) {
      this.removeArguments(res, res);
      return true;
    }
    return false;
  },
  handleFlagWithParam: function handleFlagWithParam(aFlag, aCaseSensitive) {
    return null;
  },
  STATE_INITIAL_LAUNCH: 0,
  STATE_REMOTE_AUTO: 1,
  STATE_REMOTE_EXPLICIT: 2,
  get state getState() {
    return this.STATE_INITIAL_LAUNCH;
  },
  preventDefault: false,
  workingDirectory: null,
  windowContext: null,
  resolveFile: function resolveFile (aArgument) {
    return null;
  },
  resolveURI: function resolveURI (aArgument) {
    return null;
  },
  QueryInterface: function(aIID) {
    if (!aIID.equals(Ci.nsICommandLine)
        && !aIID.equals(Ci.nsISupports))
      throw Cr.NS_ERROR_NO_INTERFACE;
    return this;
  }
}

function do_test() {
  // initialization
  let pb = Cc[PRIVATEBROWSING_CONTRACT_ID].
           getService(Ci.nsIPrivateBrowsingService).
           QueryInterface(Ci.nsIObserver);

  let testcl = new testprivatecl();

  pb.observe(testcl, "command-line-startup", null);

  let catMan = Cc["@mozilla.org/categorymanager;1"].
               getService(Ci.nsICategoryManager);
  let categories = catMan.enumerateCategory("command-line-handler");
  while (categories.hasMoreElements()) {
    let category = categories.getNext().QueryInterface(Ci.nsISupportsCString).data;
    let contractID = catMan.getCategoryEntry("command-line-handler", category);
    let handler = Cc[contractID].getService(Ci.nsICommandLineHandler);
    handler.handle(testcl);
  }

  // the private mode should be entered automatically
  do_check_true(pb.privateBrowsingEnabled);
  // and should appear as auto-started!
  do_check_true(pb.autoStarted);
}
