import Augmentor

p = Augmentor.Pipeline("C:/Users/lawle/Desktop/training/X")

p.random_distortion(probability=0.5, grid_width=3, grid_height=3, magnitude=4)
p.resize(probability=1, width=32, height=32)

p.sample(1350)