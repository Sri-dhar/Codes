class Value:
    """ stores a single scalar value and its gradient """

    def __init__(self, data, _children=(), _op=''):
        self.data = data
        self.grad = 0
        # internal variables used for autograd graph construction
        self._backward = lambda: None
        self._prev = set(_children)
        self._op = _op # the op that produced this node, for graphviz / debugging / etc

    """
    This is the constructor of the `Value` class, which is responsible for initializing an instance
    of the class. Each instance stores a scalar `data` value, and its corresponding `grad` (gradient) 
    initialized to 0. Additionally, the constructor tracks its `_prev` attribute, which holds references
    to the parent nodes, and an operation `_op` that produced this value. The `_backward` lambda is 
    initially set as a placeholder and will be populated when needed for backpropagation.
    """

    def __add__(self, other):
        other = other if isinstance(other, Value) else Value(other)
        out = Value(self.data + other.data, (self, other), '+')

        def _backward():
            self.grad += out.grad
            other.grad += out.grad
        out._backward = _backward

        return out

    """
    The `__add__` method defines the addition operation between two `Value` objects. If the `other` 
    operand is not already a `Value` instance, it is wrapped in one. The addition result is stored in
    a new `Value` object, with the parents being the operands (`self` and `other`) and the operation 
    denoted as '+'. The nested `_backward` function defines how the gradient flows back to each operand, 
    and it is assigned to the `out` object for future use during backpropagation.
    """

    def __mul__(self, other):
        other = other if isinstance(other, Value) else Value(other)
        out = Value(self.data * other.data, (self, other), '*')

        def _backward():
            self.grad += other.data * out.grad
            other.grad += self.data * out.grad
        out._backward = _backward

        return out

    """
    The `__mul__` method implements the multiplication operation between two `Value` objects. Similar to 
    the addition method, it checks if the `other` operand is a `Value` instance. It then computes the product 
    of the scalar values, stores the result in a new `Value` object, and records the parent nodes and operation.
    The `_backward` function, which will be invoked during backpropagation, calculates how the gradient flows 
    back to both operands based on the chain rule of calculus.
    """

    def __pow__(self, other):
        assert isinstance(other, (int, float)), "only supporting int/float powers for now"
        out = Value(self.data**other, (self,), f'**{other}')

        def _backward():
            self.grad += (other * self.data**(other-1)) * out.grad
        out._backward = _backward

        return out

    """
    The `__pow__` method is responsible for raising the `Value` object to a given power. It ensures that 
    the power (`other`) is either an integer or a float. It creates a new `Value` object for the result 
    and keeps track of the parent node (`self`). The `_backward` function defines how the gradient should flow 
    back to the base during backpropagation, using the derivative of the power function (i.e., 
    n*x^(n-1)) to compute the gradient.
    """

    def relu(self):
        out = Value(0 if self.data < 0 else self.data, (self,), 'ReLU')

        def _backward():
            self.grad += (out.data > 0) * out.grad
        out._backward = _backward

        return out

    """
    The `relu` method implements the Rectified Linear Unit (ReLU) activation function, which outputs the input 
    value if it is greater than 0, otherwise it returns 0. A new `Value` object is created for the result. 
    The `_backward` function calculates the gradient during backpropagation. The gradient only flows backward 
    if the output is greater than 0, as per the properties of the ReLU function.
    """

    def backward(self):

        topo = []
        visited = set()
        
        def build_topo(v):
            if v not in visited:
                visited.add(v)
                for child in v._prev:
                    build_topo(child)
                topo.append(v)
        build_topo(self)

        self.grad = 1
        for v in reversed(topo):
            v._backward()

    """
    The `backward` method initiates the backpropagation process to calculate the gradients. It builds a 
    topological ordering of the computation graph (starting from the current node) using depth-first search.
    The `topo` list stores nodes in the order in which their gradients should be calculated. Once the graph 
    is ordered, the method sets the gradient of the output node to 1 (since ∂output/∂output = 1), then 
    propagates gradients through the graph in reverse topological order by calling each node’s `_backward` function.
    """

    def __neg__(self): # -self
        return self * -1

    """
    The `__neg__` method implements negation, making it possible to negate a `Value` object (i.e., `-self`). 
    It returns the result of multiplying the object by -1.
    """

    def __radd__(self, other): # other + self
        return self + other

    """
    The `__radd__` method handles the addition when the `Value` object appears on the right-hand side of 
    the `+` operator (i.e., `other + self`). It returns the result of the addition.
    """

    def __sub__(self, other): # self - other
        return self + (-other)

    """
    The `__sub__` method defines subtraction between two `Value` objects. It computes the result by 
    negating the `other` operand and then adding it to `self`.
    """

    def __rsub__(self, other): # other - self
        return other + (-self)

    """
    The `__rsub__` method handles subtraction when the `Value` object appears on the right-hand side 
    of the `-` operator (i.e., `other - self`). It negates `self` and adds it to `other`.
    """

    def __rmul__(self, other): # other * self
        return self * other

    """
    The `__rmul__` method handles multiplication when the `Value` object appears on the right-hand side 
    of the `*` operator (i.e., `other * self`). It returns the product of `other` and `self`.
    """

    def __truediv__(self, other): # self / other
        return self * other**-1

    """
    The `__truediv__` method defines division (i.e., `self / other`) by multiplying `self` with the 
    reciprocal of `other`. It uses the `__pow__` method to compute `other**-1` and then multiplies the result.
    """

    def __rtruediv__(self, other): # other / self
        return other * self**-1

    """
    The `__rtruediv__` method handles division when the `Value` object appears on the right-hand side 
    of the `/` operator (i.e., `other / self`). It computes the result by multiplying `other` with 
    the reciprocal of `self`.
    """

    def __repr__(self):
        return f"Value(data={self.data}, grad={self.grad})"

    """
    The `__repr__` method provides a string representation of the `Value` object for easy debugging and 
    visualization. It returns the `data` value and the current gradient associated with the object.
    """
