/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace be.belgium.eid {

using System;
using System.Runtime.InteropServices;

/// <summary>
/// Exception class Command Not Allowed (error code = EIDMW_ERR_CMD_NOT_ALLOWED).
/// Throw when the command asked is not allowed.
/// Used in : 
/// - BEID_SmartCard::writeFile()
/// </summary>
public class BEID_ExCmdNotAllowed : BEID_Exception {
  private HandleRef swigCPtr;

  internal BEID_ExCmdNotAllowed(IntPtr cPtr, bool cMemoryOwn) : base(beidlib_dotNetPINVOKE.BEID_ExCmdNotAllowedUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(BEID_ExCmdNotAllowed obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~BEID_ExCmdNotAllowed() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        beidlib_dotNetPINVOKE.delete_BEID_ExCmdNotAllowed(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public BEID_ExCmdNotAllowed() : this(beidlib_dotNetPINVOKE.new_BEID_ExCmdNotAllowed(), true) {
  }

}

}
