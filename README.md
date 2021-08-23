<h1>NetworkExporter/h1>
This is a simple prometheus exporter that uses lsof command to get information about the network ports in use, and generate a prom file to be read by node_exporter.

<h3>ToDo</h3>
- Transform the application into a daemon
- add the time parameter for the scrapping interval
- Get the parameters in a conf file
- build the rpm of the project
- change the limit of the max list