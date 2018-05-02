# lakTrie
A trie of nodes that act as operators and/or operator arguments

# Demo

```
lakType lakTypeAdd(shared_ptr<vector<lakType>> args)
{
    if (args->size() < 2) return nullptr;
    try {
        return (uint8_t) ((*args)[0].getStrict<uint8_t>() + (*args)[1].getStrict<uint8_t>());
    }
    catch (lak_type_exception e) {
        return nullptr;
    }
}

int main()
{
    lakNode n1, n2, n3;
    n1 = lakTypeAdd;        // node is set to an operator
    n2 = (uint8_t) 0x10;    // node is set to a uint8_t argument
    n3 = (uint8_t) 0x10;    // node is set to a uint8_t argument
    n1.child.resize(2);
    n1.child[0] = make_shared<lakNode>(n2);
    n1.child[1] = make_shared<lakNode>(n3);
    try {
        cout << n1().getStrict<uint8_t>();  // execute n1 and strictly cast its return value to a uint8_t
    } catch (lak_type_exception e) {
       cout << "n1() did not return a uint8_t";
    }
    return 0;
}
```