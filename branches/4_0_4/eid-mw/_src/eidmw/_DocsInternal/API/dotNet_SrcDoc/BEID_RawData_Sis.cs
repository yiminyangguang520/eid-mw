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

public class BEID_RawData_Sis : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal BEID_RawData_Sis(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(BEID_RawData_Sis obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~BEID_RawData_Sis() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        beidlib_dotNetPINVOKE.delete_BEID_RawData_Sis(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
    }
  }

  public BEID_ByteArray idData {
    set {
      beidlib_dotNetPINVOKE.BEID_RawData_Sis_idData_set(swigCPtr, BEID_ByteArray.getCPtr(value));
      if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      IntPtr cPtr = beidlib_dotNetPINVOKE.BEID_RawData_Sis_idData_get(swigCPtr);
      BEID_ByteArray ret = (cPtr == IntPtr.Zero) ? null : new BEID_ByteArray(cPtr, false);
      if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public BEID_RawData_Sis() : this(beidlib_dotNetPINVOKE.new_BEID_RawData_Sis(), true) {
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
