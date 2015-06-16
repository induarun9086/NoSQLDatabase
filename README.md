# NoSQL DataBase Implementation:

 Download the zip and build the project with the following commands
 
   * Navigate to the project folder in the command prompt.
   * Run "cmake CMakeLists.txt" to configure the cmake environment.
   * When completed build the project via the "make" command.
   
 When the project has been built completely follow the instruction below to run
 
        1. Run "lauchserver.bat" which will start the server.
        2. Run "launchclient.bat" which will start the client.
        3. If multiple clients are required, run launchclient.bat again.
 
 The inputs has to be entered in the client consoles only, there is no need for commands in 
 the server console. The server console is only for viewing debug messages. The possible
 commands that can be entered in the client console are as follows, 
	
    1. open - Opens a connection.
       Connection has to be opened because, the server has to know how many clients are connected.
       
    2. event {add/update} - Register for events.
       Register notifications functionality for add/update to the connected client.
 
    3. unregister {add/update} - Unregister registered events.
       Unregister the registered event(s) for the connected client.
 
    4. add {itemName} {Description} {Price} - Add an item.
       Adds items with given details to the Nosql Database
 
    5. list -  List the items.
       Lists the items in the database.
 
    6. details {itemid} - Details of an item.
       Details of the item with given itemid.
 
    7. update {itemid} {itemName} {Description} {Price} - Updates the given item.
       Update the item with the given itemid and the given details.
	   
