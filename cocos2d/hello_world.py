# coding=UTF8
import cocos
from cocos.actions import *

class HelloWorld(cocos.layer.ColorLayer):
    def __init__(self):
        super(HelloWorld,self).__init__(64,64,224,255)

        label = cocos.text.Label(u'爱情公寓',
                                 font_name='Times New Roman',
                                 font_size=32,
                                 anchor_x='center',
                                 anchor_y='center')
        label.position = 320,240
        self.add(label,z=2)

        sprite = cocos.sprite.Sprite('aqgy.jpg')
        sprite.position = 320,240
        #sprite.scale = 3
        self.add(sprite,z=1)

        scale = ScaleBy(3,duration=2)
        # label 执行放大缩小 在这里是文字
        # Repeat是一个action的子类
        # Reverse也是 reverse是反转这个action
        # action 可以相加
        label.do(Repeat(scale+Reverse(scale)))

        # sprite是pyglet的子类 图片接口 这是图片的动画
        sprite.do(Repeat(Reverse(scale) + scale))

        

if __name__ == '__main__':
    cocos.director.director.init()
    hello_layer = HelloWorld()
    layer_action = RotateBy(360, duration=1)
    hello_layer.do(layer_action)
    main_scene = cocos.scene.Scene(hello_layer)
    cocos.director.director.run(main_scene)

