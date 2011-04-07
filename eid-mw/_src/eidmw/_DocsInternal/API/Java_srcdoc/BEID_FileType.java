/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.belgium.eid;

/******************************************************************************//**
  * Class that holds the different file type definitions
  *********************************************************************************/
public final class BEID_FileType {
	/**
	 * unknown file type
	 */
  public final static BEID_FileType BEID_FILETYPE_UNKNOWN = new BEID_FileType("BEID_FILETYPE_UNKNOWN", beidlibJava_WrapperJNI.BEID_FILETYPE_UNKNOWN_get());
	/**
	 * TLV filetype
	 */
  public final static BEID_FileType BEID_FILETYPE_TLV = new BEID_FileType("BEID_FILETYPE_TLV");
	/**
	 * XML file type
	 */
  public final static BEID_FileType BEID_FILETYPE_XML = new BEID_FileType("BEID_FILETYPE_XML");
	/**
	 * CSV file type
	 */
  public final static BEID_FileType BEID_FILETYPE_CSV = new BEID_FileType("BEID_FILETYPE_CSV");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static BEID_FileType swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + BEID_FileType.class + " with value " + swigValue);
  }

  private BEID_FileType(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private BEID_FileType(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private BEID_FileType(String swigName, BEID_FileType swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static BEID_FileType[] swigValues = { BEID_FILETYPE_UNKNOWN, BEID_FILETYPE_TLV, BEID_FILETYPE_XML, BEID_FILETYPE_CSV };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

