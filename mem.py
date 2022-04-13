#!/usr/bin/env python3.5
import resource

rsrc = resource.RLIMIT_AS

soft, hard = resource.getrlimit(rsrc)
print("Limit starts as:", soft, hard)

resource.setrlimit(rsrc, (1e8, 1e8))
soft, hard = resource.getrlimit(rsrc)
print("Limit is now:", soft, hard)

print("Allocating 5 , should certainly work")
arr = []
arr = [0 for i in range(5)] 

print("Allocating 500000 , with 1e8 should work")
arr = [0 for i in range(500000)] 
resource.setrlimit(rsrc, (1e7, 1e7))
soft, hard = resource.getrlimit(rsrc)
print("Limit is now:", soft, hard)

print("Allocating 500000 , with 1e7, should fail")
arr = [0 for i in range(500000)] 

input("Still here…")
