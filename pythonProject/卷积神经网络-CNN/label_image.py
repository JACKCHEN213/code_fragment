# Copyright 2017 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
import os
import argparse
import sys
import shutil

import numpy as np
import pandas as pd
import tensorflow as tf


# FIXME: Could not locate zlibwapi.dll. Please make sure it is in your library path!
# https://blog.csdn.net/XUQIAN_LIUQIAN/article/details/132289781


def load_graph(model_file):
    graph = tf.compat.v1.Graph()
    # graph_def = tf.GraphDef()
    graph_def = tf.compat.v1.GraphDef()

    with open(model_file, "rb") as f:
        graph_def.ParseFromString(f.read())
    with graph.as_default():
        tf.import_graph_def(graph_def)

    return graph


def read_tensor_from_image_file(file_name, input_height=299, input_width=299,
                                input_mean=0, input_std=255):
    input_name = "file_reader"
    output_name = "normalized"
    file_reader = tf.compat.v1.read_file(file_name, input_name)
    if file_name.endswith(".png"):
        image_reader = tf.image.decode_png(file_reader, channels=3,
                                           name='png_reader')
    elif file_name.endswith(".gif"):
        image_reader = tf.squeeze(tf.image.decode_gif(file_reader,
                                                      name='gif_reader'))
    elif file_name.endswith(".bmp"):
        image_reader = tf.image.decode_bmp(file_reader, name='bmp_reader')
    else:
        image_reader = tf.image.decode_jpeg(file_reader, channels=3,
                                            name='jpeg_reader')
    float_caster = tf.cast(image_reader, tf.float32)
    dims_expander = tf.expand_dims(float_caster, 0)
    resized = tf.compat.v1.image.resize_bilinear(dims_expander, [input_height, input_width])
    normalized = tf.compat.v1.divide(tf.subtract(resized, [input_mean]), [input_std])
    sess = tf.compat.v1.Session()
    result = sess.run(normalized)
    return result


def load_labels(label_file):
    label = []
    proto_as_ascii_lines = tf.compat.v1.gfile.GFile(label_file).readlines()
    for l in proto_as_ascii_lines:
        label.append(l.rstrip())
    return label


def is_other(labels, index):
    print('labels[index] = ', labels[index])
    return labels[index] == 'other' or labels[index] == 'Other' or labels[index] == '非云图片'


if __name__ == "__main__":
    tf.compat.v1.disable_eager_execution()
    file_name = "src/MSI_MPG.jpg"
    model_file = 'src/inception_v3_2016_08_28_frozen.pb'
    label_file = "src/imagenet_slim_labels.txt"
    input_height = 299
    input_width = 299
    input_mean = 0
    input_std = 255
    input_layer = "input"
    output_layer = "InceptionV3/Predictions/Reshape_1"

    parser = argparse.ArgumentParser()
    parser.add_argument("--image", help="image to be processed")
    parser.add_argument("--graph", help="graph/model to be executed")
    parser.add_argument("--labels", help="name of file containing labels")
    parser.add_argument("--input_height", type=int, help="input height")
    parser.add_argument("--input_width", type=int, help="input width")
    parser.add_argument("--input_mean", type=int, help="input mean")
    parser.add_argument("--input_std", type=int, help="input std")
    parser.add_argument("--input_layer", help="name of input layer")
    parser.add_argument("--output_layer", help="name of output layer")
    args = parser.parse_args()

    if args.graph:
        model_file = args.graph
    if args.image:
        file_name = args.image
    if args.labels:
        label_file = args.labels
    if args.input_height:
        input_height = args.input_height
    if args.input_width:
        input_width = args.input_width
    if args.input_mean:
        input_mean = args.input_mean
    if args.input_std:
        input_std = args.input_std
    if args.input_layer:
        input_layer = args.input_layer
    if args.output_layer:
        output_layer = args.output_layer

    graph = load_graph(model_file)
    if not os.path.isdir(file_name):
        t = read_tensor_from_image_file(file_name,
                                        input_height=input_height,
                                        input_width=input_width,
                                        input_mean=input_mean,
                                        input_std=input_std)
        input_name = "import/" + input_layer
        output_name = "import/" + output_layer
        input_operation = graph.get_operation_by_name(input_name)
        output_operation = graph.get_operation_by_name(output_name)

        with tf.compat.v1.Session(graph=graph) as sess:
            results = sess.run(output_operation.outputs[0],
                               {input_operation.outputs[0]: t})
        results = np.squeeze(results)

        top_k = results.argsort()[-5:][::-1]
        labels = load_labels(label_file)
        for i in top_k:
            print(labels[i], results[i])
    else:
        path_name = file_name
        input_name = "import/" + input_layer
        output_name = "import/" + output_layer
        input_operation = graph.get_operation_by_name(input_name)
        output_operation = graph.get_operation_by_name(output_name)
        labels = load_labels(label_file)
        predict_columns_name = ['FileName', 'Top1', 'Top2', 'Top3', 'Top4', 'Top5']
        predict_result = pd.DataFrame(data=None, columns=predict_columns_name)
        predict_dir = path_name + '\\PredictResult'
        if not os.path.exists(predict_dir):
            os.mkdir(predict_dir)
        for file_name in os.listdir(path_name):
            file_name_abs = path_name + '\\' + file_name
            if os.path.isdir(file_name_abs):
                continue
            print(file_name_abs)
            t = read_tensor_from_image_file(file_name_abs,
                                            input_height=input_height,
                                            input_width=input_width,
                                            input_mean=input_mean,
                                            input_std=input_std)
            with tf.compat.v1.Session(graph=graph) as sess:
                results = sess.run(output_operation.outputs[0],
                                   {input_operation.outputs[0]: t})
            results = np.squeeze(results)
            top_k = results.argsort()[-5:][::-1]
            new_result = [file_name]
            for i in top_k:
                print('\t', labels[i], results[i])
                new_result.append('%s  %.4f' % (labels[i], results[i]))
            new_result = np.array(new_result).reshape(1, -1)
            # predict_result = pd.concat((predict_result, pd.DataFrame(data=new_result, columns=predict_columns_name)),
            # axis=0)
            pr = predict_dir + '\\' + labels[top_k[0]]
            if not os.path.exists(pr):
                os.mkdir(pr)
            pr_file = pr + '\\' + file_name
            shutil.copy(file_name_abs, pr_file)
        # predict_result.to_excel('result.xls', index=False)
