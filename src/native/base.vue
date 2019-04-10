<template>
    <div class="wxc-demo">
        <head></head>
        <div> <input class="input" type="text" placeholder="search" return-key-type="search" @return="search" v-model="text" /></div>
        <scroller>
        <div class="cell" v-for="(lst,index) in list" @click="onSelected(lst,index)">
            <text class="item">{{lst.Name}}</text>
        </div>
        </scroller>s
    </div>
</template>

<script>
    import { WxcCity } from 'weex-ui';
    const  pref=weex.requireModule('pref');
    let send=''
    export default {
        components: { WxcCity },
      data(){
          return {  name: "base",
              list:[],
              text:''
          }
      },   methods: {
            onLoad(p){


                var self=this
                self.list.splice( self.list,0,self.list.length)
                send =p.send
                //self.alert(self.list.length)
                //self.list.splice(0,self.list.length);
                const net = weex.requireModule('net');
                net.post(pref.getString('ip')+'/select.do?'+p.send,{currPage:"1"},{},function(){
                    //start
                },function(e){
                    //success
                    //  self.back=e.res;
                    //  self.list.splice(0,self.list);
                    var array= e.res.obj;


                    for (var i=0;i<array.length;i++) {
                        var map = {};
                       if(p.send==='getEmployee'){
                        map.id=array[i].EmployeeID;
                        map.Name = array[i].Name;
                        self.list.push(map);
                       }
                    }

                },function(e){
                    //compelete

                },function(){
                    //exception
                });



            },
            onSelected(lst,index){
                let nav=weex.requireModule('navigator');
                nav.backFull(lst,true);
            },search(){
                if(this.text!=''){
                   let self=this
                    const net = weex.requireModule('net');
                    net.post(pref.getString('ip')+'/select.do?'+send,{"currPage":"1","param":this.text},{},function(){
                        //start
                    },function(e){
                        //success
                        //  self.back=e.res;
                        //  self.list.splice(0,self.list);
                        var array= e.res.obj;
                        if(array.length>0)
                        { self.list.splice(0,self.list.length)}

                        for (var i=0;i<array.length;i++) {
                            var map = {};
                            if(send==='getEmployee'){
                                map.id=array[i].EmployeeID;
                                map.Name = array[i].Name;
                                self.list.push(map);
                            }
                        }

                    },function(e){
                        //compelete

                    },function(){
                        //exception
                    });
                }
            },
            showGroupCity () {
                this.cityStyleType = 'group'
                this.$refs['wxcCity'].show();
            },
            citySelect (e) {
                this.currentCity = e.item;
            },
            onInput (e) {
            }
        }





    }
</script>

<style scoped>
    .input {
        border-width: 1px;

        height: 100px;
    }
    .cell{

        align-items: center;
        justify-content: center;
    }
.item{
   line-height: 80px;
    border-bottom-width: 1px;
    border-bottom-color: #eeeeee;
    width: 750px;
    align-items: center;
    justify-content: center;

}
</style>