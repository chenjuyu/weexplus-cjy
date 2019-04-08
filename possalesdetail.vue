<template>
    <div style="background-color: #eeeeee">
        <head></head>
     <div class="form">
     <div style="flex-direction: row">    <text>售货员</text> <input ref="widget" class="input" type="text" @focus="handleFocus" @blur="handleBlur" @return="handleReturn" v-model ="emp.Name"/>
     </div>
      <div style="flex-direction: row">   <text>VIP</text> <input ref="widget" class="input" type="text" @focus="handleFocus" @blur="handleBlur" @return="handleReturn" v-model ="vip.vip"/>
      </div>
       <div style="flex-direction: row">   <text>数量</text><input type="number" v-model="qty"/>
       </div>
       <div style="flex-direction: row">    <text>货品</text> <input ref="widget" class="input" type="text" @focus="handleFocus" @blur="handleBlur" @return="handleReturn" v-model ="goods.code"/>
       </div>
       </div>

     <div class="listhead" style="flex-direction: row">
      <text>货品</text><text>颜色</text><text>尺码</text><text>数量</text>
       <text>折扣</text><text>单价</text><text>金额</text>
     </div>
     <div class="cell" v-for="(ls,index) in list"></div>
        <text>{{ls.Code}}</text><text>{{ls.Color}}</text><text>{{ls.Size}}</text><text>{{ls.Quantity}}</text>
        <text>{{ls.Discount}}</text><text>{{ls.UnitPrice}}</text><text>{{ls.Amount}}</text>


        <div style="height: 100;width: 750;position: absolute;bottom: 0;left: 0;right: 0;background-color: #0088fb">
        <div style="flex-direction: row">
            <text>折让</text><input type="number" v-model="DiscountSum"/>
            <text>实付</text><input type="number" v-model="AmountSum">
        </div>
            <div style="flex-direction: row">
                <text>积分</text><input type="number" v-model="Point"/>
                <text>抵扣</text><input type="number" v-model="Discount">
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
                    employeeid:'',
                    Name :''
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

        },methods:{
            onLoad(p){
              this.alert("接收参数"+p);
              this.alert("No的值："+p.No+",madeby的值："+p.madeby);
                //console.log(p)

            },
            focus() {
                this.$refs.widget.focus();
            },
            blur() {
                this.$refs.widget.blur();
            },
            handleFocus() {
                toast('获得焦点');
            },
            handleBlur() {
                toast('失去焦点');
            },
            handleReturn() {
                toast('点击了回车按钮');
            }

        },
        created() {

        }
    }
</script>

<style scoped>

</style>