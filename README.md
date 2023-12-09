# Managing-Bank-Accounts-with-Hashing
Course Project (COL106) under Prof. Subodh Sharma [August 2023] : 
Designed and implemented an efficient bank account information management system using arrays, which included the
integration of collision resolution techniques such as chaining, linear, quadratic, and cubic probing, and double hashing.
# Strategies implemented
1) Chaining 
In the chaining strategy, the goal is to manage collisions by creating linked lists at each hash table index.
Each list handles all accounts that share the same hash code. Through this approach, you will ensure that
data remains organized and accessible even when hash function collisions arise.
2) Linear Probing 
Linear probing is your next tool, allowing you to navigate hash table slots in a linear fashion to find the next
available space when a collision occurs. This strategy emphasizes proximity and aims to avoid gaps in your
hashmap.
3) Quadratic Probing 
The quadratic probing strategy introduces a more sophisticated approach by using quadratic increments to
find the next available slot. This technique strikes a balance between proximity and distribution, providing
an alternative to linear probing.
4) Cubic Probing 
Taking the concept further, cubic probing employs cubic increments to search for open slots. This strategy
adds an extra layer of complexity to the probe sequence, aiming to distribute data evenly and mitigate
clustering issues.
# Function Description
1) void createAccount(string id, int count) : This function creates a new account with the given id and initial count value. The id uniquely identifies the account, and the count parameter represents the initial balance of the account.
2) vector<int> getTopK(int k) : Retrieves the top k balances values from the database. Returns a vector containing at most k balances values.
3) int getBalance(string id) : Returns the current balance of the account identified by the provided id. In case the id is not present return -1
4) void addTransaction(string id, int count) : Adds a transaction of count value to the account specified by the id. If the account is not already present, create a new one and then add this transaction. The transaction amount can be positive or negative, representing deposits or withdrawals, respectively.
5) bool doesExist(string id) : Checks if an account with the given id exists in the database. Returns true if the account exists, and false otherwise.
6) int databaseSize() : Returns the total number of accounts currently stored in the database.
7) int hash(string id) : This function computes the hash value for the given id. Use this hash function only in your strategies.
8) bool delete(string id) : This function deletes the key stored in database. It will return true after deletion. If the key was not present, then it should return false
