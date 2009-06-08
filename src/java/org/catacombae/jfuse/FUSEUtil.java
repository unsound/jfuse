/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

import java.io.UnsupportedEncodingException;

/**
 *
 * @author erik
 */
public class FUSEUtil {
    public static byte[] encodeUTF8(String str) {
        try {
            // TODO: Encode properly and deal with errors.
            return str.getBytes("UTF-8");
        } catch(UnsupportedEncodingException e) {
            throw new RuntimeException("UTF-8 charset not found! This should not happen...", e);
        }
    }

    public static String decodeUTF8(byte[] utf8Data) {
        try {
            // TODO: Decode properly and deal with errors.
            return new String(utf8Data, 0, utf8Data.length, "UTF-8");
        } catch(UnsupportedEncodingException e) {
            throw new RuntimeException("UTF-8 charset not found! This should not happen...", e);
        }
    }
}
