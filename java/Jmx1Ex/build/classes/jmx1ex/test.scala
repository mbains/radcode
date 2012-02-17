/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import org.eclipse.jetty.server.handler.AbstractHandler
import org.eclipse.jetty.server.Handler
import org.eclipse.jetty.server.Server
import org.eclipse.jetty.server.Request
import javax.servlet.http.HttpServletRequest
import javax.servlet.http.HttpServletResponse
import scala.xml.Elem

class test {

  val handler = new MutableHandler()

  def run(port: Int) = {
    val server = new Server(port)
    server.setHandler(handler)
    server.start()
  }

  def updateHtml(html: Elem) = {
    handler.html = html
  }
}

protected class MutableHandler extends AbstractHandler {
  var html = <h1>Hello</h1>

  override def handle(target: String, request: HttpServletRequest, response: HttpServletResponse) = {
    response.setContentType("text/html");
    response.setStatus(HttpServletResponse.SC_OK);
    response.getWriter().println(html.toString());
    (request.asInstanceOf[Request]).setHandled(true);
  }
}
