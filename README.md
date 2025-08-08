For those using, please mind you should configure the config.json in /resources before long usage and look at main.cpp for how to initialize (only Server.h required for implementation)

Dependencies:
[nlohmann/json](https://github.com/nlohmann/json) - Required for reading config.json

Release:
Release is from CMake build and **intended** to be used on Linux-based systems.

<h1>HTTP Request Usage</h1>
<h2>1A: GET method</h3>
<p>Call path is how it is called within html files, file path is how the server retrieves the file</p>
<table>
  <tr>
    <th>Name</th>
    <th>Call Path</th>
    <th>File Path</th>
    <th>Intended Usage</th>
    <th>Forced Path</th>
  </tr>
  <tr>
    <td>Favicon</td>
    <td>images/favicon.ico</td>
    <td>images/favicon.ico</td>
    <td>Webpage icon</td>
    <td>true</td>
  </tr>
  <tr>
    <td>CSS</td>
    <td>fileName.css</td>
    <td>html/fileName.css</td>
    <td>CSS Files</td>
    <td>true</td>
  </tr>
  <tr>
    <td>Images</td>
    <td>images/fileName.*</td>
    <td>images/fileName.*</td>
    <td>Calling of images</td>
    <td>false</td>
  </tr>
  <tr>
    <td>Page</td>
    <td>page/fileName</td>
    <td>html/fileName.html</td>
    <td>Returns fileName.html</td>
    <td>true</td>
  </tr>
  <tr>
    <td>Files</td>
    <td>files/fileName.*</td>
    <td>files/fileName.*</td>
    <td>Returns fileName.*</td>
    <td>false</td>
  </tr>
</table>
<h3>1B: Other request methods not currently support</h3>
<h6>Other methods are not currently supported but can be if requested, simply open a <a href="https://github.com/ImBubbles/CPP-HTTP/issues">issue</a> describing what implementation you would like</p>