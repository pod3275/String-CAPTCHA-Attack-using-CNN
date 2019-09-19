---
title: 'Augmentor: An Image Augmentation Library for Machine Learning'
tags:
  - image augmentation
  - machine learning
  - neural networks
authors:
 - name: Marcus D Bloice
   orcid: 0000-0002-2468-4086
   affiliation: 1
 - name: Christof Stocker
   orcid: 0000-0002-1276-7976
 - name: Andreas Holzinger
   orcid: 0000-0002-6786-5194
   affiliation: 1
affiliations:
 - name: Institute for Medical Informatics, Statistics and Documentation, Medical University of Graz, Austria
   index: 1
date: 22 Sep 2017
bibliography: paper.bib
---

# Summary

Augmentor is an image augmentation library for machine learning. It provides a stochastic, pipeline-based API for the generation of image data by effectively allowing new image data to be sampled at runtime according to a user-defined set of operations and parameters. Common operations include arbitrary rotations, mirroring, shearing, skewing, and random crops, as well as less frequently implemented operations such as randomised elastic distortions or random erasing [@simard2003; @zhong2017].

The pipeline approach means that images are passed through a user-defined set of operations sequentially, where each operation is applied stochastically according to a probability parameter that is also defined by the user.

The goal of the package, therefore, is to:

- Provide a platform and framework independent image augmentation library for machine learning with a convenient API
- Provide a library that is extensible, by allowing for custom operations to be added easily, even at runtime
- Provide less commonly implemented operations, such as the aforementioned elastic distortions
- Enable fine level control of parameters of the augmentation procedure

The software is available in Python [@augmentorPython] and Julia [@augmentorJulia] versions, the latter being optimised for speed [@bloice2017]. The authors would also like the thank all those who have contributed to the project, a list of whom can be found on the contributors page of the GitHub repository: <https://github.com/mdbloice/Augmentor/graphs/contributors>.

# References
