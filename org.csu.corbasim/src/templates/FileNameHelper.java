package templates;

import org.csu.idl.idlmm.Include;
import org.csu.idl.idlmm.TranslationUnit;

public class FileNameHelper {

	public static String getFileName(TranslationUnit tu) {
		return removeExtension(tu.eResource().getURI().toString()); // why?
	}
	
	public static String getFileName(Include include) {
		return removeExtension(include.getImportURI());
	}

	/**
	 * Private internal method to extract file's name (without extension).
	 * @param s path to a file.
	 * @return file's name without extension.
	 */
	private static String removeExtension(String s) {

		String separator = System.getProperty("file.separator");
		String filename;

		// Remove the path upto the filename.
		int lastSeparatorIndex = s.lastIndexOf(separator);
		if (lastSeparatorIndex == -1) {
			filename = s;
		} else {
			filename = s.substring(lastSeparatorIndex + 1);
		}

		// Remove the extension.
		int extensionIndex = filename.lastIndexOf(".");
		if (extensionIndex == -1)
			return filename;

		return filename.substring(0, extensionIndex);
	}

}
