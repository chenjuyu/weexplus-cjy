<template>
    <div class="wrapper">
        <head></head>
        <div class="form">
            <div style="flex-direction: row;justify-content:flex-start;align-items: center;margin-top: 10px">
                <text class="text">售货员</text>

                <div class="btn" @click="handleClick">
                    <text class="btn-text" :style="{'color':color}">{{emp.Name}}</text>
                </div>

            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">VIP</text>
                <div class="btn" @click="handleClick">
                    <text class="btn-text">{{vip.vip}}</text>
                </div>
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">数量</text>
                <input class="input" type="number" v-model="qty"/>
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">货品</text>
                <div class="btn" @click="handleClick">
                    <text class="btn-text">{{goods.code}}</text>
                </div>
            </div>
        </div>
     <scroller scroll-direction='horizontal'>
        <div class="listhead" style="flex-direction: row">
            <text style="width: 150px">货品</text><text style="width: 100px">颜色</text><text style="width: 100px">尺码</text><text style="width: 100px">数量</text>
            <text style="width: 100px">折扣</text><text style="width: 100px">单价</text><text style="width: 100px">金额</text>
        </div>
         <scroller>
        <div class="cell" v-for="(ls,index) in list">
            <text style="width: 150px">{{ls.Code}}</text>
            <text style="width: 100px">{{ls.Color}}</text>
            <text style="width: 100px">{{ls.Size}}</text>
            <text style="width: 100px">{{ls.Quantity}}</text>
            <text style="width: 100px">{{ls.Discount}}</text>
            <text style="width: 100px">{{ls.UnitPrice}}</text>
            <text style="width: 100px">{{ls.Amount}}</text>
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
            <div style="flex-direction: row">
                <text>合计：</text><text>{{QuantitySum}} ￥{{AmountSum}}</text>
            </div>
        </div>
    </div>
</template>

<script>
    export default {
        data() {
            return {
                name: "possalesdetail",
                DiscountSum:0.0,
                AmountSum:0.0,
                QuantitySum:0,
                Point:0,
                Discount:0.0,
                list:[],
                qty:1,
                emp:{
                    employeeid:'01A',
                    Name :'请选择售货员'
                },
                vip:{
                    vipid:'',
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
            },handleClick(){
                let nav=weex.requireModule('navigator');
                nav.pushFull({url:'root:base.js',param: {"send": "getEmployee"},
                    animate:true,
                    isPortrait:true},(res)=>{
                    if (res !=undefined) {
                        this.emp.employeeid = res.id;
                        this.emp.Name = res.Name;
                        this.color = '#000'
                        this.alert(this.emp.employeeid);
                    }
                    //this.alert(res);
                });
            }
        },
        created() {

        }
    }
</script>

<style scoped>
    .wrapper{
        width: 750px;
        background-color:#eeeeee;
        display: block;
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
    }
    .cell{
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        margin-top: 0;
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
        height: 200px;width: 750px; position: fixed;bottom: 0;left: 0;right: 0;background-color: #0088fb
    }
    .text{
        width:100px;
       direction: ltr;
    }
</style>
