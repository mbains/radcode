package intro;

import java.net.*;
import java.io.*;


public class AddClient {

  public final static String DEFAULT_SERVER 
   = "http://localhost:8080";
  public final static String SOAP_ACTION 
   = "add";

  public static void main(String[] args) {
  

    String server = DEFAULT_SERVER;
    
    try {
      URL u = new URL(server);
      URLConnection uc = u.openConnection();
      HttpURLConnection connection = (HttpURLConnection) uc;
      
      connection.setDoOutput(true);
      connection.setDoInput(true);
      connection.setRequestMethod("POST");
      connection.setRequestProperty("SOAPAction", SOAP_ACTION);
      connection.setRequestProperty("Content-type", "text/xml; charset='UTF-8'");
      
      OutputStream out = connection.getOutputStream();
      Writer wout = new OutputStreamWriter(out);
      
      wout.write("<?xml version='1.0' encoding='UTF-8'?>\r\n");
      wout.write("<SOAP-ENV:Envelope ");
        wout.write("SOAP-ENV:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'\r\n");
        wout.write("xmlns:SOAP-ENC='http://schemas.xmlsoap.org/soap/encoding/'\r\n");
        wout.write("xmlns:xsi='http://www.w3.org/1999/XMLSchema-instance'\r\n");
        wout.write("xmlns:SOAP-ENV='http://schemas.xmlsoap.org/soap/envelope/'\r\n");
        wout.write("xmlns:xsd='http://www.w3.org/1999/XMLSchema'\r\n >");
        wout.write("<SOAP-ENV:Body>\r\n");
     

      wout.write("      <add SOAP-ENC:root='1'>\r\n");
      wout.write("         <a xsi:type='xsd:int'>4</a>\r\n");
      wout.write("         <b xsi:type='xsd:int'>5</b>\r\n");
      wout.write("      </add>\r\n");

      wout.write("  </SOAP-ENV:Body>\r\n");
      wout.write("</SOAP-ENV:Envelope>\r\n"); 
      
      wout.flush();
      wout.close();
      
      InputStream in = connection.getInputStream();
      int c;
      while ((c = in.read()) != -1) System.out.write(c);
      in.close();

    }
    catch (IOException e) {
      System.err.println(e); 
    }
  
  } // end main

} // end FibonacciSOAPClient

