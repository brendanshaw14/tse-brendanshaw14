# CS50 TSE Querier
## Readme

### Errors 

No errors exist in the querier to my knowledge. 

I have investigated accuracy of the results in smaller indexes and am yet to find an error. 
I've also run thousands (literally) of fuzz queries, none of which have displayed error. Memory leaks do not exist in any of these tests. 

### Limitations

The only limitation that must be discussed is that the querier is only constructed to handle up to 200 words per query, so going over this could cause a memory issue. 

However, I have handled this by building in error messages and a return statement that will prevent any overwriting from occuring. 

