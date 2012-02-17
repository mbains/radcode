
package webrequest;

import javafx.io.http.HttpRequest;
import javafx.io.http.HttpHeader;
import javafx.animation.Timeline;
import javafx.animation.KeyFrame;

def testContent: String = "test content";
def testContentSize: Integer = testContent.getBytes().length;

var timeline : Timeline = Timeline {
    repeatCount: Timeline.INDEFINITE
    keyFrames:
        KeyFrame {
            time: 2s
            action: doRequest

        }

}

function doRequest():Void
{
    var postRequest: HttpRequest = HttpRequest {
        location:"http://localhost:8880/form";
        method: HttpRequest.POST;
        headers: [  HttpHeader {name: HttpHeader.CONTENT_TYPE;
                                value: "text/xml; charset='UTF-8'"},
                    HttpHeader {name: HttpHeader.CONTENT_LENGTH,
                                value: "{testContentSize}"}];

        onStarted: function() {
            println("onStarted - started performing method {postRequest.method} on location: {postRequest.location}");
        }

        onConnecting: function() {println("onConnecting")}
        onDoneConnect: function() {println("onDoneConnect")}
        onWriting: function() {println("onWriting")}

        onOutput:function(ostream: java.io.OutputStream) {
            try {
                println("onOutput - about to write {testContentSize} bytes to output stream");
                ostream.write(testContent.getBytes());
            }
            finally {
                println("onOutput - about to close output stream");
                ostream.close();
            }
        }

        onToWrite: function (bytes: Long) { println("onToWrite - entire content to be written: {bytes} bytes")}
        onWritten: function (bytes: Long) { println("onWritten - {bytes} bytes have now been written")}

        onDoneWrite: function() {println("onDoneWrite")}

            onReadingHeaders: function() { println("onReadingHeaders") }
        onResponseCode: function(code:Integer) { println("onResponseCode - responseCode: {code}") }
        onResponseMessage: function(msg:String) { println("onResponseMessage - responseMessage: {msg}") }

        onResponseHeaders: function(headerNames: String[]) {
            println("onResponseHeaders - there are {headerNames.size()} response headers:");
            for (name in headerNames) {
                println("    {name}: {postRequest.getResponseHeaderValue(name)}");
            }
        }

        onReading: function() { println("onReading") }

        onToRead: function(bytes: Long) {
            if (bytes < 0) {
                println("onToRead - Content length not specified by server; bytes: {bytes}");
            } else {
                println("onToRead - total number of content bytes to read: {bytes}");
            }
        }

        // The onRead callback is called when some more data has been read into
        // the input stream's buffer.  The input stream will not be available until
        // the onInput call back is called, but onRead can be used to show the
        // progress of reading the content from the location.
        onRead: function(bytes: Long) {
            // The toread variable is non negative only if the server provides the content length
            def progress =
            if (postRequest.toread > 0) "({(bytes * 100 / postRequest.toread)}%)" else "";
            println("onRead - bytes read: {bytes} {progress}");
        }

        // The content of a response can be accessed in the onInput callback function.
        // Be sure to close the input sream when finished with it in order to allow
        // the HttpRequest implementation to clean up resources related to this
        // request as promptly as possible.
        onInput: function(is: java.io.InputStream) {
            // use input stream to access content here.
            // can use input.available() to see how many bytes are available.
            try {
                println("onInput - bytes of content available: {is.available()}");
                var parser =  InputParser{};
                parser.parse(is);
                println("People = { for (person in parser.people) "{person.toStr()}\n "}");
            } finally {
                is.close();
            }
        }

        onException: function(ex: java.lang.Exception) {
            println("onException - exception: {ex.getClass()} {ex.getMessage()}");
        }

        onDoneRead: function() { println("onDoneRead") }
        onDone: function() { println("onDone") }
    }
    postRequest.start();
}

timeline.play();


