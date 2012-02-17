/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package jmx1ex;

import java.lang.management.ManagementFactory;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.management.InstanceAlreadyExistsException;
import javax.management.MBeanRegistrationException;
import javax.management.MBeanServer;
import javax.management.MalformedObjectNameException;
import javax.management.NotCompliantMBeanException;
import javax.management.ObjectName;

/**
 *
 * @author bains
 */
public class MyAgent {

    private MBeanServer mbs = null;

    public MyAgent() throws Exception {
        // get the platform MBeanServer
        mbs = ManagementFactory.getPlatformMBeanServer();

        //unique identification of MBeans
        MyfMXBean beanie = new MainClass();
        ObjectName beanieName = null;
        try {
            beanieName = new ObjectName("jmx1ex:type=MainClass");
        } catch (MalformedObjectNameException ex) {
            Logger.getLogger(MyAgent.class.getName()).log(Level.SEVERE, null, ex);
        } catch (NullPointerException ex) {
            Logger.getLogger(MyAgent.class.getName()).log(Level.SEVERE, null, ex);
        }

        
        try {
            mbs.registerMBean(beanie, beanieName);
        } catch (InstanceAlreadyExistsException ex) {
            Logger.getLogger(MyAgent.class.getName()).log(Level.SEVERE, null, ex);
        } catch (MBeanRegistrationException ex) {
            Logger.getLogger(MyAgent.class.getName()).log(Level.SEVERE, null, ex);
        }
        catch (NotCompliantMBeanException ex) {
            Logger.getLogger(MyAgent.class.getName()).log(Level.SEVERE, "not compliant", ex);
        }

    }

}
