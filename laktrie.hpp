#include <memory>
using std::shared_ptr;
using std::make_shared;
#include <vector>
using std::vector;
#include <stdint.h>
#include <exception>
using std::exception;
#include <type_traits>
using std::remove_reference;
#include "laktype.hpp"

#ifndef LAKTRIE_H
#define LAKTRIE_H

typedef lakType (*lakOperator)(shared_ptr<vector<lakType>>);

struct lakNode
{
    bool isOperation = false;
    lakOperator operation;
    lakType argument = nullptr;
    vector<shared_ptr<lakNode>> child;
    lakType operator()()
    {
        vector<lakType> args(child.size());
        for(size_t i = 0; i < child.size(); i++)
        {
            if(child[i]->isOperation) args[i] = (*(child[i]))();
            else args[i] = child[i]->argument;
        }
        return operation(make_shared<vector<lakType>>(args));
    }
    void operator=(lakType arg){ argument = arg; isOperation = false; }
    void operator=(lakOperator op){ operation = op; isOperation = true; }
    lakNode(){}
    lakNode(const lakNode& other){ 
        isOperation = other.isOperation;
        operation = other.operation;
        argument = other.argument;
        child = other.child;
    }
    lakNode(lakNode&& other){ 
        isOperation = other.isOperation;
        operation = other.operation;
        argument = other.argument;
        child = other.child;
    }
    lakNode(const lakType& arg){ argument = arg; isOperation = false; }
    lakNode(lakType&& arg){ argument = arg; isOperation = false; }
    lakNode(lakOperator op){ operation = op; isOperation = true; }
};

#endif