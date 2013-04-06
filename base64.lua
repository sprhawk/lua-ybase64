require("ybase64")

if #arg == 0 then
   print("uasge:" .. arg[-1] .. " " .. arg[0] .. " sample.dat")
   return 
end

file = io.open(arg[1], "rb")
str = file:read("*all")
print("str:" .. tostring(#str))
aa = ybase64.encode(str)
print(aa)