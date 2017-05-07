function [a2] = not()

X = [0 0; 0 1; 1 0; 1 1]
Y = [0; 0; 0; 1]

theta = [284549524,1505041484]
theta2
for i = 1:2
	a1 = X(i, :)'
	a2 = 1./(1 + exp(-(theta*a1)))
			
	delta = a2 - Y(i)
end
