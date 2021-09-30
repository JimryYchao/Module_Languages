
func = function(...)
    local a1 = select(1, ...)
    local a2 = select(2, ...)
    print(a1 + a2)
end

a,b,c = pcall(func, 1, 3, 4)

print(a,b,c)

arr = {}

do  
    print(666)
    return arr
end

arr[1] = undef