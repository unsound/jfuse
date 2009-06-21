/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.catacombae.jfuse;

import java.util.Iterator;
import java.util.LinkedList;

/**
 *
 * @author erik
 */
public class FUSEOptions {

    private final LinkedList<Option> optionList = new LinkedList<Option>();

    public void addOption(String name, String value) {
        if(name.contains(",") || value.contains(","))
            throw new IllegalArgumentException("The character ',' is reserved" +
                    " and can not exist in the name or value of an option.");

        removeOption(name);
        optionList.addLast(new Option(name, value));
    }

    public void addOption(String name) {
        if(name.contains(","))
            throw new IllegalArgumentException("The character ',' is reserved" +
                    " and can not exist in the name or value of an option.");
        
        removeOption(name);
        optionList.addLast(new Option(name));
    }

    public boolean removeOption(String name) {
        for(Iterator<Option> it = optionList.iterator(); it.hasNext(); ) {
            Option o = it.next();
            if(o.name.equals(name)) {
                it.remove();
                return true;
            }
        }
        return false;
    }

    /**
     *
     * @param name the name of the option.
     * @return the value associated with the option <code>name</code>.
     * @throws NullPointerException if there is no option defined for
     * <code>name</code>.
     */
    public String getOptionValue(String name) {
        for(Iterator<Option> it = optionList.iterator(); it.hasNext(); ) {
            Option o = it.next();
            if(o.name.equals(name)) {
                return o.value;
            }
        }

        throw new NullPointerException();
    }

    public String[] getDefinedOptions() {
        String[] result = new String[optionList.size()];

        int i = 0;
        for(Iterator<Option> it = optionList.iterator(); it.hasNext();) {
            result[i++] = it.next().name;
        }
        
        return result;
    }

    public void setDebug(Boolean b) {
        final String debugOption = "debug";
        if(b)
            addOption(debugOption);
        else
            removeOption(debugOption);
    }
    
    public void setForeground(Boolean b) {
        final String foregroundOption = "-f";
        if(b)
            addOption(foregroundOption);
        else
            removeOption(foregroundOption);
    }

    public void setSingleThreaded(Boolean b) {
        final String singleThreadedOption = "-s";
        if(b)
            addOption(singleThreadedOption);
        else
            removeOption(singleThreadedOption);
    }

    public void setFsname(String fsname) {
        addOption("fsname", fsname);
    }

    public String[] generateOptionStrings() {
        String[] result = new String[optionList.size()];

        int i = 0;
        for(Iterator<Option> it = optionList.iterator(); it.hasNext();) {
            Option o = it.next();
            result[i++] = "-o" + o.name + (o.value != null ? "=" + o.value : "");
        }

        return result;
    }

    protected static class Option {
        public final String name;
        public final String value;

        public Option(String name) {
            if(name == null)
                throw new IllegalArgumentException("No null names allowed.");

            this.name = name;
            this.value = null;
        }

        public Option(String name, String value) {
            if(name == null)
                throw new IllegalArgumentException("No null names allowed.");
            if(value == null)
                throw new IllegalArgumentException("No null values allowed. (Use the empty constructor)");

            this.name = name;
            this.value = value;
        }
    }
}
