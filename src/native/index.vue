<template>
    <div class="layout">
      <div class="ig">  <image class="img" src="root:img/logo.png" @click="gonext"></image> </div>

        <wxc-cell title="用户名"
                  :has-arrow="false"
                  :has-top-border="false">
            <input class="input" type="text" placeholder="输入用户名" return-key-type="default" v-model="username" />
        </wxc-cell>

        <wxc-cell title="密    码"
                  :has-arrow="false"
                  :has-top-border="false">
        <input class="input" type="password" placeholder="输入密码" return-key-type="default"  v-model="password" />
        </wxc-cell>
        <div class="demo">
        <wxc-button text="登录" type="white" style="height: 95px"
                    @wxcButtonClicked="wxcButtonClicked"></wxc-button>
        </div>
        <div class="ip"><text @click="jump">配置服务器地址</text></div>
    </div>



</template>
<script>
    //<text class="text" @click="scan">扫描条码/二维码</text>
    //<text class="text">欢迎使用</text>
   // const nav=weex.registerModule('navigator')
    import { WxcButton,WxcCell } from 'weex-ui'
    const net = weex.requireModule('net');
    const  pref=weex.requireModule('pref');
    const url='/login.do?login';
    export default{
        components: { WxcButton ,WxcCell },
        data(){
            return {
                username:'',
                password:'',
                list:[]
            }
        },
        props: {},
        methods: {
            onLoad(p){

            },
            gonext(){
             //  debugger
              //  this.push('test.js',{name:"中文内容"})




            },
            scan(){

                    var qr=weex.requireModule('qr')
                    var p={};
                    p.color='#000000'
                    p.bgcolor='#ffffff'
                    qr.open(p,(res)=>{
                        var url=res;
                        this.alert(url);
                    })

            },jump(){
                this.push("root:test.js");
            },
            wxcButtonClicked (e) {
               // this.alert("name的值 ："+this.username);
                var parma={};
                parma.username=this.username;
                parma.password=this.password;
               // console.log(e);
                if (parma !=='')
                net.post(pref.getString('ip')+url,parma,{},function () {
                    //start
                }, (e)=>{
                    //this.alert(e.obj)
                    //success
                  //  debugger
                    console.log("res对象:"+e.res);
                    console.log("res对象里的obj对象中的username:"+e.res.obj.UserName);

                 //  var obj1 = eval('(' + JSON.stringify(e.res) + ')'); //字符串转成对象
                  //  console.log("数据返回的数据："+obj1);
                 //   console.log("数据返回的obj："+obj1.obj.UserName);
                    //this.alert(e.Obj);
                },function(e){
                    //compelete

                },function(e){
                    //exception
                  //  this.alert("返回数据失败")
                });

                this.push('root:Possales.js');
            }
        },
        created(){

        }
    }
</script>
<style scoped>
    /*
    align-items:center;
      background-color:#eeeeee;
     justify-content: center;
    */
  .layout{
      justify-content: center;
      background-color:#eeeeee;
      text-align: center;

}
    .ig{
        align-items:center;
        background-color:#eeeeee;
        justify-content: center;
    }
 .img{
     align-items: center;
     width: 200px;
     height: 200px;
     margin-top: 10px;
 }
 .text{
     color: black;
     margin-top: 30px;
     font-size: 70px;
     font-weight: bold;
 }

.input {
    borderColor: '#eeeeee';
    backgroundColor: '#eeeeee';
   height: 50px;
   width:600px;
}
.demo{
    align-items: center;
    margin-top:30px;
 }
  .ip{
      display: block;
      width: 702px;
      margin-top:60px;
      direction:rtl;

    }
</style>