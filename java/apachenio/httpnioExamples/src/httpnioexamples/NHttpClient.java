/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package httpnioexamples;

import org.apache.http.impl.nio.reactor.DefaultConnectingIOReactor;
import org.apache.http.nio.reactor.ConnectingIOReactor;
import org.apache.http.nio.reactor.IOReactorException;
import org.apache.http.params.HttpParams;
import org.apache.http.params.SyncBasicHttpParams;

/**
 *
 * @author boozer
 */
public class NHttpClient {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOReactorException {
        // TODO code application logic here
        HttpParams params = new SyncBasicHttpParams();
        final ConnectingIOReactor ioReactor = new DefaultConnectingIOReactor(2, params);
        

    }

}
