require "ifj21"


function main() -- uzivatelska funkce bez parametru
  local a : integer
  write("Zadejte cislo pro vypocet faktorialu\n")
  a = readi()
  write(a)
end

function chrCall()
	local a : nil
	chr(a)
end

function writeCall()
	local a : string
	local b : integer
	local c : number
	local d : boolean
	local e : string

	a="ahoj"
	b=10
	c=20.1
	d=true
	e="\10"
	write(a,e,b,e,c,e,d,e)
end

function ordCall()
	local a : string
	local b : integer
	local c : integer
	-- local d : nil
	
	a = "ahoj"
	b = 2
	c = ord(a,b)
	write(c)

	-- c = ord(b,b)
	-- c = ord(d,b)
end

writeCall()

