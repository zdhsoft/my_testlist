import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
def main():
    print('hello world!')
    model = keras.Sequential(
        [
            layers.Dense(2, activation="relu", name="layer1"),
            layers.Dense(3, activation="relu", name="layer2"),
            layers.Dense(4, name="layer3"),
        ]
    )
    # Call model on a test input
    x = tf.ones((3, 3))
    y = model(x)
    x1 = tf.ones((3, 3))
    y1 = layer3(layer2(layer1(x)))

if __name__ == '__main__':
    main()

