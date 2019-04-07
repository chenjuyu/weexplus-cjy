<template>
    <div class="layout">

            <head leftButton=""></head>
       <scroller>
        <!--九宫格显示  <text class="iconfont bar-ic">&#xe614;</text> 动态显示要 即：字体编码后前四位是Unicode编码，想使用字符串来传递的话,只要将 “&#xe64b;” 改为 “\ue64b” 即可。-->
       <div style="margin-top: 10px;"><text>基本资料</text></div>
        <div class="sudoku_row">
        <div class="sudoku_item " :class="curSelect===sudoku.id?'opacity':''"   v-for="(sudoku,index) in sudokus" :key="index" @touchstart="touchstart(index)" @touchend="touchend" >
            <div> <!-- <image :src="sudoku.img_src" style="width:72px;height: 72px;" ></image> -->
            <text class="iconfont bar-ic" style="width: 72px;height: 72px">{{sudoku.img_src}}</text>
             <text>{{sudoku.name}} </text>
             </div>
          </div>
          </div>
          <!--九宫格显示 -->
           <div style="margin-top: 10px;"><text>采购管理</text></div>
           <div class="sudoku_row">
               <div class="sudoku_item " :class="curSelect===sudoku.id?'opacity':''"   v-for="(sudoku,index) in sudokus" :key="index" @touchstart="touchstart(index)" @touchend="touchend" >
                   <div> <text class="iconfont bar-ic" style="width: 72px;height: 72px">{{sudoku.img_src}}</text>
                       <text>{{sudoku.name}} </text>
                   </div>
               </div>
           </div>

           <!--九宫格显示 -->
           <div style="margin-top: 10px;"><text>分销管理</text></div>
           <div class="sudoku_row">
               <div class="sudoku_item " :class="curSelect===sudoku.id?'opacity':''"   v-for="(sudoku,index) in sudokus" :key="index" @touchstart="touchstart(index)" @touchend="touchend" >
                   <div> <text class="iconfont bar-ic" style="width: 72px;height: 72px">{{sudoku.img_src}}</text>
                       <text>{{sudoku.name}} </text>
                   </div>
               </div>
           </div>

           <!--九宫格显示 -->
           <div style="margin-top: 10px;"><text>库存管理</text></div>
           <div class="sudoku_row">
               <div class="sudoku_item " :class="curSelect===sudoku.id?'opacity':''"   v-for="(sudoku,index) in sudokus" :key="index" @touchstart="touchstart(index)" @touchend="touchend" >
                   <div> <text class="iconfont bar-ic" style="width: 72px;height: 72px">{{sudoku.img_src}}</text>
                       <text>{{sudoku.name}} </text>
                   </div>
               </div>
           </div>

           <!--九宫格显示 -->
           <div style="margin-top: 10px;"><text>零售管理</text></div>
           <div class="sudoku_row">
               <div class="sudoku_item " :class="curSelect===sudoku.id?'opacity':''"   v-for="(sudoku,index) in sudokus" :key="index" @touchstart="touchstart(index)" @touchend="touchend" >
                   <div> <text class="iconfont bar-ic" style="width: 72px;height: 72px">{{sudoku.img_src}}</text>
                       <text>{{sudoku.name}} </text>
                   </div>
               </div>
           </div>


       </scroller>
    </div>
</template>

<script>

    export default {
        name: "GridViveList",
        components:{


        },
        data() {
            return {
                sudokus:[{
                    id:0,
                    name:'飞机',
                    img_src:'\ue614' //https://gw.alicdn.com/tfs/TB1kCk2SXXXXXXFXFXXXXXXXXXX-72-72.png
                },{
                    id:1,
                    name:'游戏',
                    img_src:'\ue614'//require('../static/img/game.png')
                },{
                    id:2,
                    name:'音乐',
                    img_src:'\ue614'//require('../static/img/music.png')
                },{
                    id:3,
                    name:'物流',
                    img_src:'\ue614'//require('../static/img/logistics.png')
                },{
                    id:4,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                },{
                    id:5,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                },{
                    id:6,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                },{
                    id:7,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                },{
                    id:8,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                },{
                    id:9,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                },{
                    id:10,
                    name:'医院',
                    img_src:'\ue614'//require('../static/img/hospital.png')
                }],

            };
        },props:{
            curSelect:{
                default:100
            }
        },created(){
         /*   let domModule = weex.requireModule('dom');
            domModule.addRule('fontFace',{
                'fontFamily': "iconfont",
                'src': "url('http://at.alicdn.com/t/font_1074303_e64s32fcc65.ttf')"
            }) */
        },
        methods:{
            touchstart:function(e){
               /* this.alert(e)
                this.curSelect=Number(e)
                 var that = this;
                  var list = that.sudokus;
                  for (var i = 0, len = list.length; i < len; ++i) {
                      if (list[i].id == e) {
                          that.curSelect = i;
                      }
                  } */
            },touchend:function(){
                this.alert('触发这里了')
                var that = this;
                that.curSelect = null;
            }
        }

    }
</script>

<style scoped>
    .iconfont {
        font-family:iconfont;  /*必须写哦！！ */
    }
    .bar-ic{
        padding-top: 14px;
        font-size: 38px;
        color: red;
    }
    .layout{



      /*  display: flex;
        align-items: center;
        width:100%;
        flex-wrap: wrap; */
    }
    .sudoku_row{

       background-color: #5ac3ff;
        flex-direction:row;
        flex-wrap: wrap;


    }
    .sudoku_item{
     /*   flex:1; display: flex;  justify-content: center;*/


        justify-content: center;
        align-items:center;
        width: 250px;
        height: 150px;
        border-width:1;
        border-color: #eeeeee;

    }
    .opacity{
        opacity: 0.4;
        background: #e5e5e5;
    }
    .sudoku_item img{
        margin-bottom: 3px;
        display: block;
    }


</style>