Examples
========

A number of typical usage scenarios are described here.

.. note::

    A full list of operations can be found in the :mod:`.Operations` module documentation.

Initialising a pipeline
-----------------------

.. code-block:: python
    
     import Augmentor

     path_to_data = "/home/user/images/dataset1/"

     # Create a pipeline
     p = Augmentor.Pipeline(path_to_data)

Adding operations to a pipeline
-------------------------------

.. code-block:: python

    # Add some operations to an existing pipeline.

    # First, we add a horizontal flip operation to the pipeline:
    p.flip_left_right(probability=0.4)

    # Now we add a vertical flip operation to the pipeline:
    p.flip_top_bottom(probability=0.8)

    # Add a rotate90 operation to the pipeline:
    p.rotate90(probability=0.1)

Executing a pipeline
--------------------

.. code-block:: python

    # Here we sample 100,000 images from the pipeline.

    # It is often useful to use scientific notation for specify
    # large numbers with trailing zeros.
    num_of_samples = int(1e5)

    # Now we can sample from the pipeline:
    p.sample(num_of_samples)
