<template>
    <div class="wrapper">
        <head></head>
        <div class="form">
            <div style="flex-direction: row;justify-content:flex-start;align-items: center;margin-top: 10px">
                <text class="text">售货员</text>

                <div class="btn" @click="handleClick(1)">
                    <text class="btn-text" :style="{'color':color}">{{emp.Name}}</text>
                </div>

            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">VIP</text>
                <div class="btn" @click="handleClick(2)">
                    <text class="btn-text">{{vip.vip}}</text>
                </div>
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">数量</text>
                <input class="input" type="number" v-model="iqty"/>
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">货品/条码</text>
                <input class="input" type="number" v-model="barcode" @return="search"/>
             <!--   <div class="btn" @click="handleClick()">
                    <text class="btn-text">{{goods.code}}</text>
                </div> -->

            </div>
        </div>
     <scroller  style="width: 1100px" scroll-direction='horizontal'>
        <div  style="flex-direction: row">
            <text class="cellitem">条码</text>
            <text style="width: 150px">货品</text>
            <text class="cellitem">颜色</text>
            <text class="cellitem">尺码</text>
            <text class="cellitem">数量</text>
            <text class="cellitem">折扣</text>
            <text class="cellitem">单价</text>
            <text class="cellitem">金额</text>
        </div>
         <scroller>
        <div class="cell" v-for="(ls,index) in list">
            <text class="cellitem">{{ls.BarCode}}</text>
            <text style="width: 150px;height: 30px">{{ls.GoodsCode}}</text>
            <text class="cellitem">{{ls.ColorName}}</text>
            <text class="cellitem">{{ls.SizeName}}</text>
            <text class="cellitem">{{iqty}}</text>
            <text class="cellitem">{{ls.Discount|numFilter}}</text>
            <text class="cellitem">{{ls.UnitPrice|numFilter}}</text>
            <text class="cellitem">{{ls.Amount}}</text>
        </div>
         </scroller>
     </scroller>
        <div  class="tabbar">
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text>折让</text><input type="number" :disabled="true" v-model="DiscountSum" style="width: 300px;height: 70px;border-bottom-width:1px;"/>
                <text>实付</text><input type="number" :disabled="true" v-model="AmountSum" style="width: 300px;height: 70px;border-bottom-width:1px;">
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text>积分</text><input type="number" :disabled="true" v-model="Point" style="width: 300px;height: 70px;border-bottom-width:1px;"/>
                <text>抵扣</text><input type="number" :disabled="true" v-model="Discount" style="width: 300px;height: 70px;border-bottom-width:1px;">
            </div>
            <div style="flex-direction: row; background-color: red; position: fixed;bottom: 0;left: 0;right: 0;height: 80px;align-items: center;justify-content:flex-start">
                <text>合计：</text><text>{{QuantitySum}}</text><text>￥{{AmountSum}}</text>
                <div style="background-color: orange;position: fixed;right: 0;bottom: 0;width: 250px;height: 80px;align-items: center;justify-content:center"><text @click="save">保存</text></div>
            </div>


        </div>
    </div>
</template>

<script>
    const  pref=weex.requireModule('pref');
    export default {
        data() {
            return {
                name: "possalesdetail",
                show:false,
                DiscountSum:0.0,
                amount:0.0,
                type:'销售单',
                Point:0,
                Discount:0.0,
                barcode:'',
                list:[],
                iqty:1,
                qty:0,
                emp:{
                    employeeId:'',
                    Name :'请选择售货员'
                },
                vip:{
                    vipId:'',
                    vipCode:'',
                    vip:''
                },
                goods:{
                    goodsid:'',
                    code:'',
                    Name:''
                }
            }
        },
        props:{
            color:{
                default:"#eeeeee"
            }
        },methods:{
            onLoad(p){
                // this.alert("接收参数"+p);
                // this.alert("No的值："+p.No+",madeby的值："+p.madeby);
                //console.log(p)
            },
            focus() {
                this.$refs.widget.focus();
            },
            blur() {
                this.$refs.widget.blur();
            },
            handleFocus() {
                // toast('获得焦点');
                //
            },
            handleBlur() {
                //toast('失去焦点');
            },
            handleReturn() {
                //toast('点击了回车按钮');
            },
            change(){
            },
            input(){
            },handleClick(id){
                let nav=weex.requireModule('navigator');
                let wherestr="";
                if (id===1){
                    wherestr= "getEmployee"
                }else if(id===2){
                    wherestr= "getVip"
                }

                nav.pushFull({url:'root:base.js',param: {"send": wherestr,"id":id},
                    animate:true,
                    isPortrait:true},(res)=>{
                    if (res !=undefined) {
                        if (id===1){
                        this.emp.employeeid = res.id;
                        this.emp.Name = res.Name;
                        this.color = '#000'
                        }else if(id===2){
                            this.vip.vipId=res.id
                            this.vip.vip =res.Name;
                        }
                      //  this.alert(this.emp.employeeid);
                    }
                    //this.alert(res);
                });
            },search(){
                let self=this
               if(this.barcode !='')
               {
                   const net = weex.requireModule('net');
                   net.post(pref.getString('ip')+'/select.do?analyticalBarcode',{"Type":"possales","BarCode":this.barcode},{},function(){
                       //start
                   },function(e){
                       //success
                       //  self.back=e.res;
                       //  self.list.splice(0,self.list);
                     // if(e.res.obj !=undefined)
                       var array= e.res.obj;

                     //  self.alert(e.res.obj)

                     //  debugger
                      // for (var i=0;i<array.length;i++) {
                           var map = {};
                               map.BarCode=array.BarCode;
                               map.GoodsName = array.GoodsName;
                               map.ColorName = array.ColorName;
                               map.SizeName = array.SizeName;
                               map.GoodsCode = array.GoodsCode;
                               map.Discount = array.Discount;
                               map.GoodsID = array.GoodsID;
                               map.ColorID = array.ColorID;
                               map.SizeID = array.SizeID;
                               map.UnitPrice = array.UnitPrice;
                               map.RetailSales = array.RetailSales;
                               map.Amount=self.iqty==0?1:parseFloat(self.iqty * array.UnitPrice).toFixed(2) //先单价* 数量，后台促销后面再算
                          // self.list.push(map); //最后面
                        //   self.alert(map.Amount)
                           self.list.unshift(map);
                     //  }
                     if (self.list.length>0){
                         self.show=true
                     }
                   },function(e){
                       //compelete

                   },function(){
                       //exception
                   });

               }



            }
        },
        created() {

        },
        filters: {

            numFilter(value) {

                // 截取当前数据到小数点后两位

                let realVal = parseFloat(value).toFixed(2)

                return realVal

            }

        }
    }
</script>

<style scoped>
    .wrapper{

        background-color:#eeeeee;
        display: block;
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
    }
    .cell{

        top: 0;
        left: 0;
        right: 0;
        margin-bottom: 0px;
        margin-top: 0;
        flex-direction: row;
    }
    .cellitem{
        width: 120px;
        line-height: 50px;

    }
    .input {
        border-width: 1px;
        margin-bottom: 10px;
        height: 100px;
        width: 750px;
        background-color: #FFF;
    }
    .btn {
        padding-top: 30px;
        padding-bottom: 20px;
        padding-left: 20px;
        padding-right: 20px;
        background-color: #FFF;
        margin-bottom: 20px;
        width: 750px;
        height: 100px;
        border-width: 1px;
        align-items: flex-start;
    }
    .btn-text {
    }
    .tabbar{
        display: block;
        height: 230px;width: 750px; position: fixed;bottom: 0;left: 0;right: 0;background-color: #0088fb
    }
    .text{
        width:100px;
       direction: ltr;
    }
</style>
