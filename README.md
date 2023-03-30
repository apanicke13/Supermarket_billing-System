# Supermarket_billing-System

This is a console-based application built using C++ programming language. It is used to manage products and store their details.

<b><h2>Requirements</b></h2>

C++ compiler

<b><h2>How to run the application</b></h2>

Clone the repository.
- Open the terminal and navigate to the cloned repository directory.
- Compile and run the program.
- Follow the instructions displayed on the console to use the application.

<b><h2>Features</b></h2>

- Add a product to the system.
- Display all products available in the system.
- Modify the details of a product.
- Delete a product from the system.
- Search for a specific product.

<b><h2>Classes</b></h2>

Product

The Product class has the following attributes:

- pno : integer
- name : character array
- price : float
- qty : float
- tax : float
- dis : float

The Product class has the following methods:

- create_product() : This method is used to create a new product and store it in the system.
- show_product() : This method is used to display the details of a product.
- retpno() : This method is used to return the product number.
- retprice() : This method is used to return the price of the product.
- retname() : This method is used to return the name of the product.
- retdis() : This method is used to return the discount percentage of the product.

<b><h2>Functions</b></h2>

- write_product() : This function is used to write a product to the file.
- display_all() : This function is used to display all the products in the system.
- admin_menu() : This function is used to display the main menu.
- AppendData() : This function is used to append data to the file.
- InsertRecord() : This function is used to insert a record into the file.
- display_sp(int) : This function is used to display a specific product.
- modify_product() : This function is used to modify the details of a product.
- delete_product() : This function is used to delete a product from the system.

<b><h2>File handling</b></h2>

The system uses file handling to store and manage the products. The file used is Shop.dat.

When a new product is added to the system, it is written to the file using the fstream class. When a product is modified or deleted, the file is opened in both in and out mode using the fstream class. The modified data is written to a temporary file named Temp.dat. The original file is then deleted, and the temporary file is renamed as the original file name.

<b><h2>Conclusion</b></h2>

This product management system provides an easy and efficient way to manage products. It is a simple yet powerful application that can be used by small businesses to manage their inventory.
