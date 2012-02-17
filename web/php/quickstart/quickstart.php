<?php
//we'll generate xml output
header('Content-Type: text/xml');
//generate XML header
echo '<?xml version="1.0" encoding="UTF-8" ?>';

//crate the <response> element
echo '<response>';

//retrieve the user name
$name = $_GET['name'];

// generate output depending on the user name received from client
$userNames = array('CRISTIAN', 'BOGDAN', 'FILIP', 'MIHAI', 'YODA');

if(in_array(strtoupper($name),$userNames))
    echo 'Hello, master ' . htmlentities($name) . '!';
else if (trim($name) == '')
    echo 'Stranger, please tell me your name!';
else
    echo htmlentities($name) . ', I dont know you!';

echo '</response>';

?>

