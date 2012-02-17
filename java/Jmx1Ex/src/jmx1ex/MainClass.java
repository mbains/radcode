/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package jmx1ex;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.eclipse.jetty.server.Server;

/**
 *
 * @author bains
 */
public class MainClass implements MyfMXBean {

    private String message_m = null;

    public MainClass() {
        message_m = "Unset";
    }
    
    public static void main(String[] args) throws Exception {
//        try {
//            MyAgent agent = new MyAgent();
//            
////              MBeanServer mbs = ManagementFactory.getPlatformMBeanServer();
////              ObjectName name = new ObjectName("jmx1ex:name=MainClass");
////              MainClass mbean = new MainClass();
////              mbs.registerMBean(mbean, name);
//            System.out.println("wait for keypress...");
//            System.in.read();
//        } catch (IOException ex) {
//            Logger.getLogger(MainClass.class.getName()).log(Level.SEVERE, null, ex);
//        }
        

    
        Server server = new Server(8080);
        server.start();
        server.join();

    }

    public void sayHello() {
        System.out.println(message_m);
    }
    
    public String getMessage() {
        return message_m;
    }

    public void setMessage(final String message) {
        message_m = message;
    }


}
