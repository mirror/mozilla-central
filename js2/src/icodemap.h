/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express oqr
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is the JavaScript 2 Prototype.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU Public License (the "GPL"), in which case the
 * provisions of the GPL are applicable instead of those above.
 * If you wish to allow use of your version of this file only
 * under the terms of the GPL and not to allow others to use your
 * version of this file under the NPL, indicate your decision by
 * deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL.  If you do not delete
 * the provisions above, a recipient may use your version of this
 * file under either the NPL or the GPL.
 */

/* most of this file will get auto-generated from the icode metadata */

#ifndef __icodemap_h

#define __icodemap_h

#include "systemtypes.h"
#include "icodeasm.h"

namespace JavaScript {
namespace ICodeASM {

static uint icodemap_size = 72;

static struct {
    char *name;
    OperandType otype[4];
} icodemap [] =
{
    {"ADD", {otRegister, otRegister, otRegister}},
    {"AND", {otRegister, otRegister, otRegister}},
    {"BITNOT", {otRegister, otRegister}},
    {"BRANCH", {otLabel}},
    {"BRANCH_FALSE", {otLabel, otRegister}},
    {"BRANCH_INITIALIZED", {otLabel, otRegister}},
    {"BRANCH_TRUE", {otLabel, otRegister}},
    {"CALL", {otRegister, otRegister, otRegister, otArgumentList}},
    {"CAST", {otRegister, otRegister, otJSType}},
    {"COMPARE_EQ", {otRegister, otRegister, otRegister}},
    {"COMPARE_GE", {otRegister, otRegister, otRegister}},
    {"COMPARE_GT", {otRegister, otRegister, otRegister}},
    {"COMPARE_IN", {otRegister, otRegister, otRegister}},
    {"COMPARE_LE", {otRegister, otRegister, otRegister}},
    {"COMPARE_LT", {otRegister, otRegister, otRegister}},
    {"COMPARE_NE", {otRegister, otRegister, otRegister}},
    {"DEBUGGER", {otNone}},
    {"DELETE_PROP", {otRegister, otRegister, otStringAtom}},
    {"DIRECT_CALL", {otRegister, otJSFunction, otArgumentList}},
    {"DIVIDE", {otRegister, otRegister, otRegister}},
    {"ELEM_XCR", {otRegister, otRegister, otRegister, otDouble}},
    {"GENERIC_BINARY_OP", {otRegister, otBinaryOp, otRegister, otRegister}},
    {"GET_ELEMENT", {otRegister, otRegister, otRegister}},
    {"GET_METHOD", {otRegister, otRegister, otUInt32}},
    {"GET_PROP", {otRegister, otRegister, otStringAtom}},
    {"GET_SLOT", {otRegister, otRegister, otUInt32}},
    {"GET_STATIC", {otRegister, otJSClass, otUInt32}},
    {"INSTANCEOF", {otRegister, otRegister, otRegister}},
    {"JSR", {otLabel}},
    {"LOAD_BOOLEAN", {otRegister, otBool}},
    {"LOAD_IMMEDIATE", {otRegister, otDouble}},
    {"LOAD_NAME", {otRegister, otStringAtom}},
    {"LOAD_STRING", {otRegister, otJSString}},
    {"MOVE", {otRegister, otRegister}},
    {"MULTIPLY", {otRegister, otRegister, otRegister}},
    {"NAME_XCR", {otRegister, otStringAtom, otDouble}},
    {"NEGATE", {otRegister, otRegister}},
    {"NEW_ARRAY", {otRegister}},
    {"NEW_CLASS", {otRegister, otJSClass}},
    {"NEW_FUNCTION", {otRegister, otICodeModule}},
    {"NEW_OBJECT", {otRegister, otRegister}},
    {"NOP", {otNone}},
    {"NOT", {otRegister, otRegister}},
    {"OR", {otRegister, otRegister, otRegister}},
    {"POSATE", {otRegister, otRegister}},
    {"PROP_XCR", {otRegister, otRegister, otStringAtom, otDouble}},
    {"REMAINDER", {otRegister, otRegister, otRegister}},
    {"RETURN", {otRegister}},
    {"RETURN_VOID", {otNone}},
    {"RTS", {otNone}},
    {"SAVE_NAME", {otStringAtom, otRegister}},
    {"SET_ELEMENT", {otRegister, otRegister, otRegister}},
    {"SET_PROP", {otRegister, otStringAtom, otRegister}},
    {"SET_SLOT", {otRegister, otUInt32, otRegister}},
    {"SET_STATIC", {otJSClass, otUInt32, otRegister}},
    {"SHIFTLEFT", {otRegister, otRegister, otRegister}},
    {"SHIFTRIGHT", {otRegister, otRegister, otRegister}},
    {"SLOT_XCR", {otRegister, otRegister, otUInt32, otDouble}},
    {"STATIC_XCR", {otRegister, otJSClass, otUInt32, otDouble}},
    {"STRICT_EQ", {otRegister, otRegister, otRegister}},
    {"STRICT_NE", {otRegister, otRegister, otRegister}},
    {"SUBTRACT", {otRegister, otRegister, otRegister}},
    {"SUPER", {otRegister}},
    {"TEST", {otRegister, otRegister}},
    {"THROW", {otRegister}},
    {"TRYIN", {otLabel, otLabel}},
    {"TRYOUT", {otNone}},
    {"USHIFTRIGHT", {otRegister, otRegister, otRegister}},
    {"VAR_XCR", {otRegister, otRegister, otDouble}},
    {"WITHIN", {otRegister}},
    {"WITHOUT", {otNone}},
    {"XOR", {otRegister, otRegister, otRegister}},
};

    VM::Instruction *InstructionFromNode (StatementNode *node)
    {
        using namespace VM;
        Instruction *i;
        
        switch (node->icodeID)
        {
            case 0:
                i = new Add (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 1:
                i = new And (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 2:
                i = new Bitnot (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 3:
                i = new Branch (reinterpret_cast<Label*>(node->operand[0].data));
                break;
            case 4:
                i = new BranchFalse (reinterpret_cast<Label*>(node->operand[0].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 5:
                i = new BranchInitialized (reinterpret_cast<Label*>(node->operand[0].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 6:
                i = new BranchTrue (reinterpret_cast<Label*>(node->operand[0].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 7:
                i = new Call (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0), static_cast<ArgumentList>(node->operand[3].data));
                break;
            case 8:
                i = new Cast (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), reinterpret_cast<JSType*>(node->operand[2].data));
                break;
            case 9:
                i = new CompareEQ (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 10:
                i = new CompareGE (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 11:
                i = new CompareGT (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 12:
                i = new CompareIN (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 13:
                i = new CompareLE (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 14:
                i = new CompareLT (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 15:
                i = new CompareNE (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 16:
                i = new Debugger ();
                break;
            case 17:
                i = new DeleteProp (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), reinterpret_cast<const StringAtom*>(node->operand[2].data));
                break;
            case 18:
                i = new DirectCall (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<JSFunction*>(node->operand[1].data), static_cast<ArgumentList>(node->operand[2].data));
                break;
            case 19:
                i = new Divide (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 20:
                i = new ElemXcr (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0), static_cast<double>(node->operand[3].data));
                break;
            case 21:
                i = new GenericBinaryOP (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), static_cast<BinaryOperator::BinaryOp>(node->operand[1].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[3].data), 0));
                break;
            case 22:
                i = new GetElement (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 23:
                i = new GetMethod (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), static_cast<uint32>(node->operand[2].data));
                break;
            case 24:
                i = new GetProp (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), reinterpret_cast<const StringAtom*>(node->operand[2].data));
                break;
            case 25:
                i = new GetSlot (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), static_cast<uint32>(node->operand[2].data));
                break;
            case 26:
                i = new GetStatic (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<JSClass*>(node->operand[1].data), static_cast<uint32>(node->operand[2].data));
                break;
            case 27:
                i = new Instanceof (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 28:
                i = new Jsr (reinterpret_cast<Label*>(node->operand[0].data));
                break;
            case 29:
                i = new LoadBoolean (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), static_cast<bool>(node->operand[1].data));
                break;
            case 30:
                i = new LoadImmediate (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), static_cast<double>(node->operand[1].data));
                break;
            case 31:
                i = new LoadName (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<const StringAtom*>(node->operand[1].data));
                break;
            case 32:
                i = new LoadString (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<JSString*>(node->operand[1].data));
                break;
            case 33:
                i = new Move (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 34:
                i = new Multiply (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 35:
                i = new NameXcr (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<const StringAtom*>(node->operand[1].data), static_cast<double>(node->operand[2].data));
                break;
            case 36:
                i = new Negate (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 37:
                i = new NewArray (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0));
                break;
            case 38:
                i = new NewClass (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<JSClass*>(node->operand[1].data));
                break;
            case 39:
                i = new NewFunction (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<ICodeModule*>(node->operand[1].data));
                break;
            case 40:
                i = new NewObject (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 41:
                i = new Nop ();
                break;
            case 42:
                i = new Not (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 43:
                i = new Or (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 44:
                i = new Posate (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 45:
                i = new PropXcr (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), reinterpret_cast<const StringAtom*>(node->operand[2].data), static_cast<double>(node->operand[3].data));
                break;
            case 46:
                i = new Remainder (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 47:
                i = new Return (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0));
                break;
            case 48:
                i = new ReturnVoid ();
                break;
            case 49:
                i = new Rts ();
                break;
            case 50:
                i = new SaveName (reinterpret_cast<const StringAtom*>(node->operand[0].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 51:
                i = new SetElement (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 52:
                i = new SetProp (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<const StringAtom*>(node->operand[1].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 53:
                i = new SetSlot (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), static_cast<uint32>(node->operand[1].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 54:
                i = new SetStatic (reinterpret_cast<JSClass*>(node->operand[0].data), static_cast<uint32>(node->operand[1].data), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 55:
                i = new Shiftleft (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 56:
                i = new Shiftright (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 57:
                i = new SlotXcr (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), static_cast<uint32>(node->operand[2].data), static_cast<double>(node->operand[3].data));
                break;
            case 58:
                i = new StaticXcr (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), reinterpret_cast<JSClass*>(node->operand[1].data), static_cast<uint32>(node->operand[2].data), static_cast<double>(node->operand[3].data));
                break;
            case 59:
                i = new StrictEQ (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 60:
                i = new StrictNE (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 61:
                i = new Subtract (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 62:
                i = new Super (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0));
                break;
            case 63:
                i = new Test (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0));
                break;
            case 64:
                i = new Throw (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0));
                break;
            case 65:
                i = new Tryin (reinterpret_cast<Label*>(node->operand[0].data), reinterpret_cast<Label*>(node->operand[1].data));
                break;
            case 66:
                i = new Tryout ();
                break;
            case 67:
                i = new Ushiftright (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;
            case 68:
                i = new VarXcr (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), static_cast<double>(node->operand[2].data));
                break;
            case 69:
                i = new Within (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0));
                break;
            case 70:
                i = new Without ();
                break;
            case 71:
                i = new Xor (TypedRegister(static_cast<JSTypes::Register>(node->operand[0].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[1].data), 0), TypedRegister(static_cast<JSTypes::Register>(node->operand[2].data), 0));
                break;

            default:
                NOT_REACHED("Unknown icodeID");
        }

        return i;
        
    }
                
 
}
}

#endif /* #ifdef __icodemap_h */
