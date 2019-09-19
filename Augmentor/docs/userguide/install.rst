Installation
============

Installation is via ``pip``:

.. code-block:: bash

    pip install Augmentor

If you have to use ``sudo`` it is recommended that you use the ``-H`` flag:

.. code-block:: bash

    sudo -H pip install Augmentor

Requirements
------------

Augmentor requires ``Pillow`` and ``tqdm``. Note that Pillow is a fork of PIL, but both packages cannot exist simultaneously. Uninstall PIL before installing Pillow.

Building
--------

If you prefer to build the package from source, first clone the repository: 

.. code-block:: bash

    git clone https://github.com/mdbloice/Augmentor.git

Then enter the ``Augmentor`` directory and build the package:

.. code-block:: bash

    cd Augmentor
    python setup.py install 

Alternatively you can first run ``python setup.py build`` followed by ``python setup.py install``. This can be useful for debugging.

.. attention::

    If you are compiling from source you may need to compile the dependencies also, including Pillow. On Linux this means having libpng (``libpng-dev``) and zlib (``zlib1g-dev``) installed.
