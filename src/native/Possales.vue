<template>
    <div class="container" :style="{ height: height }">
        <head v-bind:title="title" v-on:titleClick="titleClick">
         <text slot="right" :style="{'color':titleColor}"> 更多</text>
        </head>
       <!-- <navhead></navhead> -->
        <div><input class="input" type="text" placeholder="default" return-key-type="default" /></div>
        <div> <text  @click="getPossales" class="text1">获取小票数据</text> </div>
    <div class="plist">
        <list>
            <cell v-for="(img, i) in list" :key="i">
                <div>
                  {{img.No}}
                </div>
                <div>
                    {{img.Employee}}
                </div>
            </cell>
        </list>
    </div>




    </div>
</template>

<script>
    //<image class="image" :src="img.src"></image>
    //<text class="title" :value="i"></text>
    import navhead from './component/navhead.vue'
    const net = weex.requireModule('net');
    const  pref=weex.requireModule('pref');
  //  let navbar=weex.requireModule('navbar')
   // navbar.setStatusBarStyle('white')
    import {WxcMinibar} from 'weex-ui';

    var url='/salesTicket.do?getPossales';
    export default {
        components:{WxcMinibar,navhead},
        data() {
            return {
                name: 'Possales',
                list:[]
            }
        },
        props: {
            title:{
                default:'小票'
            },
            titleColor:{
                default:'#ffffff'
            }
        },
        methods:{
            onLoad(e){

            },
            getPossales(){
                var pa={}
                pa.beginDate='2018-01-23';
                pa.endDate='2019-03-30';
                net.post(pref.getString('ip')+url,pa,{},function () {
                    //start
                }, (e)=>{
                    this.list=e.res.obj;
                    //this.alert(e.obj)
                    //success
                   // debugger
                //    console.log("res对象:"+e.res);
                 //   console.log("res对象里的obj对象中的obj:"+e.res.obj);
                //   var array=new Array();
                 //   array=e.res.obj;
                    //  var self=this;
                   // self.list=e.res.obj;
             /*
                    for(var i=0;array.length;++i){
                        console.log(array[i].No);
                    }
               */
                    //  var obj1 = eval('(' + JSON.stringify(e.res) + ')'); //字符串转成对象
                    //  console.log("数据返回的数据："+obj1);
                    //   console.log("数据返回的obj："+obj1.obj.UserName);
                   // this.alert(e.Obj);
                },function(e){
                    //compelete

                },function(e){
                    //exception
                    this.alert("返回数据失败")
                })
            },minibarLeftButtonClick () {
                this.toast('返回上一页');
            },
            minibarRightButtonClick () {
                this.toast('返回上一页');
            },titleClick() {//head vue中的方案
                this.toast('点击标题')
            }
        }
    }
</script>

<style scoped>


    .text1{
        width: 110px;
        height: 60px;
        font-size: 50px;
        justify-content: center;
        align-items: center;
        background-color: #00B4FF;
        text-align-all: center;

    }
    .title {
        text-align: center;
        font-size: 40px;
        color: #888;
        padding: 10px;
        background-color: #EEE;
    }
    .image {
        width: 750px;
        height: 235px;
    }
    .input {
        margin-top: 20px;
        border-width: 1px;
        margin-bottom: 10px;
        height: 100px;
    }
</style>