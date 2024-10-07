import random
from micrograd.engine import Value

"""
This section imports the necessary modules. The `random` module is used for initializing weights with random values,
while the `Value` class is imported from `micrograd.engine`. The `Value` class is essential for representing 
scalar values and handling automatic differentiation within the neural network framework.
"""

class Module:

    def zero_grad(self):
        for p in self.parameters():
            p.grad = 0

    """
    The `zero_grad` method is defined within the `Module` base class. Its purpose is to reset the gradients of 
    all parameters associated with the module to zero. This is crucial to prevent the accumulation of gradients 
    from previous iterations during the training process.
    """

    def parameters(self):
        return []

    """
    The `parameters` method is a placeholder in the `Module` base class that returns an empty list. 
    It is intended to be overridden by subclasses to provide access to their respective parameters 
    (e.g., weights and biases) that require gradient computation.
    """

class Neuron(Module):

    def __init__(self, nin, nonlin=True):
        self.w = [Value(random.uniform(-1,1)) for _ in range(nin)]
        self.b = Value(0)
        self.nonlin = nonlin

    """
    The `__init__` method initializes a `Neuron` instance. It takes `nin`, the number of input connections, and 
    `nonlin`, a boolean indicating whether to apply a non-linear activation function (ReLU) after the neuron's 
    linear combination. The weights (`self.w`) are initialized with random values between -1 and 1, and the bias 
    (`self.b`) is initialized to zero. The `nonlin` attribute determines if the ReLU activation is applied.
    """

    def __call__(self, x):
        act = sum((wi*xi for wi,xi in zip(self.w, x)), self.b)
        return act.relu() if self.nonlin else act

    """
    The `__call__` method defines the forward pass of the neuron. It takes an input vector `x`, computes the 
    weighted sum of the inputs plus the bias (`act`), and then applies the ReLU activation function if 
    `self.nonlin` is `True`. If `self.nonlin` is `False`, it returns the linear combination without activation.
    This allows the neuron to act as either an activated neuron or a linear unit based on the configuration.
    """

    def parameters(self):
        return self.w + [self.b]

    """
    The `parameters` method in the `Neuron` class overrides the base class method to return a list of the neuron's 
    parameters, which include its weights (`self.w`) and bias (`self.b`). These parameters are essential for 
    gradient computations during the training process.
    """

    def __repr__(self):
        return f"{'ReLU' if self.nonlin else 'Linear'}Neuron({len(self.w)})"

    """
    The `__repr__` method provides a string representation of the `Neuron` instance. It indicates whether the 
    neuron uses a ReLU activation function or is linear, and it displays the number of input connections 
    (i.e., the number of weights). This representation is useful for debugging and visualizing the network's structure.
    """

class Layer(Module):

    def __init__(self, nin, nout, **kwargs):
        self.neurons = [Neuron(nin, **kwargs) for _ in range(nout)]

    """
    The `__init__` method initializes a `Layer` instance. It takes `nin`, the number of input connections to the 
    layer, and `nout`, the number of neurons in the layer. Additional keyword arguments (`**kwargs`) are 
    passed to each `Neuron`. The layer consists of a list of `Neuron` instances, each initialized with `nin` inputs.
    """

    def __call__(self, x):
        out = [n(x) for n in self.neurons]
        return out[0] if len(out) == 1 else out

    """
    The `__call__` method defines the forward pass of the layer. It takes an input vector `x` and passes it through 
    each neuron in the layer, collecting their outputs. If the layer contains only one neuron, it returns a single 
    `Value` object; otherwise, it returns a list of `Value` objects representing the outputs of all neurons in the layer.
    """

    def parameters(self):
        return [p for n in self.neurons for p in n.parameters()]

    """
    The `parameters` method in the `Layer` class overrides the base class method to return a flattened list of all 
    parameters from each neuron within the layer. This aggregation is essential for optimizing the entire layer's 
    parameters during training.
    """

    def __repr__(self):
        return f"Layer of [{', '.join(str(n) for n in self.neurons)}]"

    """
    The `__repr__` method provides a string representation of the `Layer` instance. It lists all neurons within 
    the layer by invoking each neuron's `__repr__` method. This representation is useful for understanding 
    the composition and structure of the layer within the neural network.
    """

class MLP(Module):

    def __init__(self, nin, nouts):
        sz = [nin] + nouts
        self.layers = [Layer(sz[i], sz[i+1], nonlin=i!=len(nouts)-1) for i in range(len(nouts))]

    """
    The `__init__` method initializes an `MLP` (Multi-Layer Perceptron) instance. It takes `nin`, the number of 
    input features, and `nouts`, a list specifying the number of neurons in each subsequent layer. The method 
    constructs the network by creating a list of `Layer` instances, where each layer connects the previous layer's 
    size to the next. The `nonlin` parameter is set to `True` for all layers except the last one, allowing the 
    network to apply non-linear activations between hidden layers while keeping the output layer linear.
    """

    def __call__(self, x):
        for layer in self.layers:
            x = layer(x)
        return x

    """
    The `__call__` method defines the forward pass of the entire MLP. It takes an input vector `x` and sequentially 
    passes it through each layer in the network. The output of each layer becomes the input to the next layer. 
    Finally, it returns the output of the last layer, which represents the MLP's prediction.
    """

    def parameters(self):
        return [p for layer in self.layers for p in layer.parameters()]

    """
    The `parameters` method in the `MLP` class overrides the base class method to return a flattened list of all 
    parameters from each layer within the network. This comprehensive list is necessary for optimizing all 
    parameters during the training process.
    """

    def __repr__(self):
        return f"MLP of [{', '.join(str(layer) for layer in self.layers)}]"

    """
    The `__repr__` method provides a string representation of the `MLP` instance. It lists all layers within 
    the network by invoking each layer's `__repr__` method. This representation is useful for visualizing the 
    overall architecture of the MLP, including the configuration of each layer.
    """
