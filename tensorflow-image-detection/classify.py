import tensorflow as tf
import sys
import os
from tensorflow.python.platform import gfile


# Disable tensorflow compilation warnings
os.environ['TF_CPP_MIN_LOG_LEVEL']='2'
import tensorflow as tf


save_loc = os.getcwd()


extensions = ['jpg', 'jpeg']
file_list = []
for extension in extensions:
    file_glob = os.path.join(os.getcwd() + "/validation_dataset/", '*.' + extension)
    file_list.extend(gfile.Glob(file_glob))


resultfile = open(save_loc + '/result.txt',"w")
count = 0


with tf.gfile.FastGFile(save_loc + "/tf_files/output_graph.pb", 'rb') as f:
    graph_def = tf.GraphDef()
    graph_def.ParseFromString(f.read())
    _ = tf.import_graph_def(graph_def, name='')


for image_path in file_list:
    # Read the image_data
    image_data = tf.gfile.FastGFile(image_path, 'rb').read()


    # Loads label file, strips off carriage return
    label_lines = [line.rstrip() for line in tf.gfile.GFile(save_loc + "/tf_files/output_labels.txt")]


    # Unpersists graph from file
    with tf.Session() as sess:
        # Feed the image_data as input to the graph and get first prediction
        softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')
    
        predictions = sess.run(softmax_tensor, \
                 {'DecodeJpeg/contents:0': image_data})
        
        # Sort to show labels of first prediction in order of confidence
        top_k = predictions[0].argsort()[-len(predictions[0]):][::-1]
    
        human_string = label_lines[top_k[0]]
        res = "%s\n" % (human_string.upper())
        resultfile.write(res)

        print("%d complete." % (count+1))

        if (count%6) == 5 :
            print()
            resultfile.write("\n")
        count = count + 1
        
resultfile.close()
