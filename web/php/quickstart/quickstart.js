var xmlHttpGlobal = createXmlHttpRequestObject();

//retrieve the XMLhttprequest object

function createXmlHttpRequestObject()
{
    var xmlHttp;
    //will store the reference to the XMLHttpRequest object
    //if running IE
    if(window.ActiveXObject)
    {
        try
        {
            xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        catch(e)
        {
            xmlHttp = false;
        }
    }
    //if running mozilla or other browsers
    else
    {
        try
        {
            xmlHttp = new XMLHttpRequest();
        }
        catch(e)
        {
            xmlHttp = false;
        }
    }
    if(!xmlHttp)
        alert("Error creating the XMLHttpRequest object")
    else
        return xmlHttp;
}

//make async. http request using the XMLHttpRequest object
function process()
{
    //proceed only if the xmlHttpGlobal object isn't busy
    if(xmlHttpGlobal.readyState == 4 || xmlHttpGlobal.readyState == 0)
    {
        //retreive the name typed by the user on the form
        name = encodeURIComponent(document.getElementById("myName").value);

        //define the php script request
        xmlHttpGlobal.open("GET", "quickstart.php?name=" + name, true);

        //define the method to handle the response
        xmlHttpGlobal.onreadystatechange = handleServerResponse;

        //make the request
        xmlHttpGlobal.send(null);
    }
    else
        {
        //if the connection is busy, try again after 1 second
            setTimeout('process()', 1000)
        }
}

function handleServerResponse()
{
    if(xmlHttpGlobal.readyState == 4)
    {
        
        //transaction completed successfully
        if(xmlHttpGlobal.status == 200)
        {
            
            //extract the xml retreived from the server
            xmlResponse = xmlHttpGlobal.responseXML;
            if (xmlResponse == null)
                alert("xmlResponse = null")
            //obtain the document element (the root element) of the xml structure
            xmlDocumentElement = xmlResponse.documentElement;
            //get the text message which is in the first child of the document element
            helloMessage = xmlDocumentElement.firstChild.data;

            // update the client dispaly using th edata received.
            document.getElementById("divMessage").innerHTML =
                '<i>' + helloMessage + ' </i>';
            
            // restart the sequence
            setTimeout('process()', 1000);
        }
        //error occured
        else
        {
            alert("There was a problem accessing the server: " + xmlHttpGlobal.statusText);
        }
    }
    
}
