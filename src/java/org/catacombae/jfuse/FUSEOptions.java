/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

import java.util.HashMap;
import java.util.Set;

/**
 *
 * @author erik
 */
public class FUSEOptions {
    private Boolean debug = null;
    private Boolean foreground = null;
    private Boolean singleThreaded = null;
    private String fsname = null;

    private final HashMap<String,String> optionMap =
            new HashMap<String,String>();

    public void setOption(String name, String value) {
        if(name.contains(",") || value.contains(","))
            throw new IllegalArgumentException("The character ',' is reserved" +
                    " and can not exist in the name or value of an option.");

        optionMap.put(name, value);
    }

    public String getOption(String name) {
        return optionMap.get(name);
    }

    public String[] getOptionNames() {
        Set<String> keySet = optionMap.keySet();
        return keySet.toArray(new String[keySet.size()]);
    }

    public void setDebug(Boolean b) {
        debug = b;
    }
    public void setForeground(Boolean b) {
        foreground = b;
    }
    public void setSingleThreaded(Boolean b) {
        singleThreaded = b;
    }
    public void setFsname(String s) {
        fsname = s;
    }
}
