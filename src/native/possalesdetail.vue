<template>
    <div class="wrapper">
        <head :rightText="rightText" title="小票"  @rightClick="rightClick"></head>
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
                <input class="input1" type="text" v-model="iqty"/>
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text class="text">货品/条码</text>
                <input class="input" type="number" v-model="barcode" @return="search" return-key-type="search"/>
                 <text class="iconfont bar-ic" @click="qrclick">&#xe69a;</text>

            </div>
        </div>

        <wxc-dialog title="详情"
                    :show="show1"
                    :single="false"
                    :is-checked="isChecked"
                    :show-no-prompt="false"
                    @wxcDialogCancelBtnClicked="wxcDialogCancelBtnClicked"
                    @wxcDialogConfirmBtnClicked="wxcDialogConfirmBtnClicked"
                    @wxcDialogNoPromptClicked="wxcDialogNoPromptClicked">

           <div slot="content" style="align-items: flex-start;line-height: 150px" >
               <div style="flex-direction: row;height: 80px;align-items: center"><text>货号:{{lmap.GoodsCode}}</text></div>
               <div style="flex-direction: row ;height: 80px;align-items: center"><text>颜色:{{lmap.ColorName}}</text></div>
               <div style="flex-direction: row;height: 80px;align-items: center"><text>尺码:{{lmap.SizeName}}</text></div>
               <div style="flex-direction: row;height: 80px;align-items: center"><text>数量:</text><input type="number" class="dialoginput" v-model="lmap.Quantity" /></div>
           </div>
        </wxc-dialog>

        <wxc-popover ref="wxc-popover"
                     :buttons="btns"
                     :position="popoverPosition"
                     :arrowPosition="popoverArrowPosition"
                     @wxcPopoverButtonClicked="popoverButtonClicked"></wxc-popover>


     <scroller  style="width: 1100px" scroll-direction='horizontal'>
        <div  style="flex-direction: row">
            <text class="cellitem">条码</text>
            <text class="cellitem">货品</text>
            <text class="cellitem">颜色</text>
            <text class="cellitem">尺码</text>
            <text class="cellitem">数量</text>
            <text class="cellitem">折扣</text>
            <text class="cellitem">单价</text>
            <text class="cellitem">金额</text>
        </div>
         <scroller>
        <div class="cell" v-for="(ls,index) in list" @longpress="handleLongPress(ls,index)">
            <text class="cellitem">{{ls.Barcode}}</text>
            <text class="cellitem">{{ls.GoodsCode}}</text>
            <text class="cellitem">{{ls.ColorName}}</text>
            <text class="cellitem">{{ls.SizeName}}</text>
            <text class="cellitem">{{ls.Quantity}}</text>
            <text class="cellitem">{{ls.Discount|numFilter}}</text>
            <text class="cellitem">{{ls.UnitPrice|numFilter}}</text>
            <text class="cellitem">{{ls.Amount}}</text>
        </div>
         </scroller>
     </scroller>
        <div  class="tabbar">
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text>折让</text><input type="number"  v-model="discountMoney" style="width: 300px;height: 70px;border-bottom-width:1px;"/>
                <text>实付</text><input type="number"  v-model="AmountSum" style="width: 300px;height: 70px;border-bottom-width:1px;">
            </div>
            <div style="flex-direction: row;justify-content:flex-start;align-items: center">
                <text>积分</text><input type="number"  v-model="Point" style="width: 300px;height: 70px;border-bottom-width:1px;"/>
                <text>抵扣</text><input type="number" :disabled="true" v-model="exchange_amount" style="width: 300px;height: 70px;border-bottom-width:1px;">
            </div>
            <div style="flex-direction: row; background-color: #1EA5FC; position: fixed;bottom: 0;left: 0;right: 0;height: 80px;align-items: center;justify-content:flex-start">
                <text>合计：</text><text>{{QuantitySum}}</text><text style="margin-left: 100px">￥{{AmountSum}}</text>
                <div  v-if="show" style="background-color: orange;position: fixed;right: 0;bottom: 0;width: 250px;height: 80px;align-items: center;justify-content:center"><text @click="save">{{savetitle}}</text></div>
            </div>


        </div>
    </div>
</template>

<script>
    const  pref=weex.requireModule('pref');
    const saveMethod="/salesTicket.do?saveSalesTicket"
    import { WxcDialog ,WxcPopover} from 'weex-ui';
    export default {
        components: { WxcDialog ,WxcPopover},
        data() {
            return {
                rightText:'\ue602',
                lmap:{},
                popoverPosition:{x:-14,y:120},
                popoverArrowPosition:{pos:'top',x:-15},
                btns:[
                    {
                        icon: 'https://gw.alicdn.com/tfs/TB1Vm3abuuSBuNjy1XcXXcYjFXa-64-64.png',
                        text:'Scan',
                        key:'key-scan'
                    },
                    {
                        icon: 'https://gw.alicdn.com/tfs/TB1U93abuuSBuNjy1XcXXcYjFXa-64-64.png',
                        text:'My Qrcode',
                        key:'key-qrcode'
                    },
                    {
                        icon: 'https://gw.alicdn.com/tfs/TB1MWDTbwmTBuNjy1XbXXaMrVXa-64-64.png',
                        text:'Help',
                        key:'key-help'
                    },
                ],
                oldqty:0,
                show1: false,
                isChecked: false,
                name: "possalesdetail",
                savetitle:'保存',
                show:false,
                AmountSum:0.00,
                discountMoney:0.00,
                QuantitySum:0,
                DiscountSum:0.0,
                amount:0.0,
                type:'销售单',
                Point:0,
                exchange_amount:0.0,
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
                    vip:'',
                    VIPTypeID:'',
                    DiscountRate:0.0,
                    vipPointRate:0,
                    UsablePoint:0
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
                        if (id===1){ //员工

                        this.emp.employeeId = res.id;
                          //  this.alert("employeeid:"+this.emp.employeeId)
                        this.emp.Name = res.Name;
                        this.color = '#000'
                        }else if(id===2){ //vip


                            this.vip.vipId=res.id
                            this.vip.vip =res.Name;
                            this.vip.vipCode=res.Code
                            this.vip.DiscountRate=res.DiscountRate
                            this.vip.UsablePoint =res.UsablePoint
                            this.vip.vipPointRate =res.vipPointRate
                            this.vip.VIPTypeID =res.VIPTypeID


                        }

                    }

                });
            },rightClick(){
                this.$refs['wxc-popover'].wxcPopoverShow();
            }, popoverButtonClicked (obj) {
               modal.toast({ 'message': `key:${obj.key}, index:${obj.index}`, 'duration': 1 });
            },
            handleLongPress(ls,index){
                //this.alert("ls"+ls.GoodsCode +",index:"+index)
                this.lmap=ls
                this.oldqty=ls.Quantity
                this.show1 = true;
            },   wxcDialogCancelBtnClicked () {
                //此处必须设置，组件为无状态组件，自己管理  取消取回原来的值
                if(this.oldqty !=this.lmap.Quantity){
                    this.lmap.Quantity=  this.oldqty
                }
                this.show1 = false;
            },
            wxcDialogConfirmBtnClicked () {
                //此处必须设置，组件为无状态组件，自己管理
                if(this.oldqty !=this.lmap.Quantity){
                   // this.lmap.Amount= Number(this.lmap.Quantity) * Number(this.lmap.Discount)/10 *Number(this.lmap.UnitPrice)
                    this.countTotal()
                }
                this.show1 = false;
            },
            qrclick(){
                const self=this
                var qr=weex.requireModule('qr')
                var p={};
                p.color='#ffffff'//'#000000'
                p.bgcolor='#00000000'//'#ffffff'
                qr.open(p,(res)=>{
                   // var url=res.url
                    //this.alert(res)
                    if(res !=undefined){
                        self.barcode=res
                        self.search()
                    }
                })
            },
            search(){
                let self=this

                if(self.emp.employeeId ==='')
                {
                    self.alert('请先选择售货员')
                    return
                }
               if(this.barcode !='')
               {

                   if (!self.isIntNum(self.iqty)){
                       self.alert('数量：请输入数字')
                       return
                   }


                   const net = weex.requireModule('net');
                   net.post(pref.getString('ip')+'/select.do?analyticalBarcode',{"Type":"possales","BarCode":this.barcode},{},function(){
                       //start
                   },function(e){
                       //success
                       //  self.back=e.res;
                       //  self.list.splice(0,self.list);
                     // if(e.res.obj !=undefined)

                       if(e.res.obj===undefined){
                           self.alert('没有找到此条码')
                          return
                       }

                       var array= e.res.obj;

                     //  self.alert(e.res.obj)

                     //  debugger

                           var map = {};
                              map.Barcode=array.BarCode;
                               map.GoodsName = array.GoodsName;
                               map.ColorName = array.ColorName;
                               map.SizeName = array.SizeName;
                               map.GoodsCode = array.GoodsCode;
                               map.Discount = self.vip.DiscountRate==0?array.Discount:Number(self.vip.DiscountRate);
                               map.DiscountRate=self.vip.DiscountRate==0?array.Discount:Number(self.vip.DiscountRate);
                               map.GoodsID = array.GoodsID;
                               map.ColorID = array.ColorID;
                               map.SizeID = array.SizeID;
                               map.UnitPrice = array.UnitPrice;
                               map.RetailSales = array.RetailSales;
                               map.Quantity=self.iqty==0?1:self.iqty


                              if (map.DiscountRate !=null) {
                                  map.DiscountPrice =Number(map.UnitPrice) * Number(map.DiscountRate)/10.0
                              }else{
                                  map.DiscountPrice=null
                              }
                             //  map.Amount=self.iqty==0?1:parseFloat(self.iqty * array.UnitPrice).toFixed(2) //先单价* 数量，后台促销后面再算
                        //  self.list.push(map); //最后面
                        //   self.alert(map.Amount)
                       // self.list.unshift(map);
                       let  mapData =self.getList(map)  //返回是否存在
                       if(mapData===null){
                           self.list.unshift(map);
                       }else{
                           mapData.Quantity=Number(mapData.Quantity)+Number(map.Quantity)
                       }
                       self.barcode='' //重置扫描区
                       self.countTotal()

                     if (self.list.length>0){
                         self.show=true
                     }

                      // self.alert("employeeId的变化"+self.emp.employeeId)
                      // self.alert("vipid的变化"+self.vip.vipId)

                   },function(e){
                       //compelete

                   },function(){
                       //exception
                   });

               }



            },countTotal(){
                //统计合计与金额 this.vip.DiscountRate !=0.0 &&
                let sumAmt=0.00
                let sumQty=0
                if( this.list.length >0){

                    for(let i=0;i< this.list.length;i++){
                       let map=  this.list[i]
                       // this.alert("map的值:"+map.UnitPrice+";Quantity的值："+map.UnitPrice*0.8025)
                        map.Amount=parseFloat(this.vip.DiscountRate==0?map.UnitPrice *map.Quantity:map.UnitPrice *map.Quantity*this.vip.DiscountRate/10.0).toFixed(2)
                        sumAmt=Number(sumAmt)+Number(parseFloat(this.vip.DiscountRate==0?map.UnitPrice *map.Quantity:map.UnitPrice *map.Quantity*this.vip.DiscountRate/10.0).toFixed(2))
                        sumQty=Number(sumQty)+Number(map.Quantity)
                    }
                 this.QuantitySum = sumQty
                 this.AmountSum   = parseFloat(sumAmt).toFixed(2)




                }

            },isIntNum(val){
                var regPos = /^[0-9]+.?[0-9]*$/;; // 非负整数
                var regNeg = /^\-[1-9][0-9]*$/; // 负整数
                if(regPos.test(val) || regNeg.test(val)){
                    return true;
                }else{
                    return false;
                }
            },getList(barcode) {  //检查ListView中的重复记录  参数也为map
                for(let i=0;i<this.list.length;i++){
                 let tempMap=this.list[i]
                  if(barcode.GoodsID===tempMap.GoodsID && barcode.ColorID===tempMap.ColorID &&barcode.SizeID===tempMap.SizeID){
                     let Quantity =tempMap.Quantity
                      if(barcode.Quantity>0 && Quantity>0){
                          return tempMap
                      }else if(barcode.Quantity<0 && Quantity<0){
                          return tempMap
                      }

                  }


                }
                return null;
            },save(){
                const self=this

                if(self.savetitle==='新增'){
                    var page=weex.requireModule("page")
                    page.reload();
                    return
                }


                const net = weex.requireModule('net');
                const progress =weex.requireModule('progress')
                var map={}
                map.data=self.list;
                map.vipId=self.vip.vipId;
                map.vipCode= self.vip.vipCode;
                map.employeeId= self.emp.employeeId;
                map.amount= self.AmountSum;
                map.retailAmount =Number(self.AmountSum)-Number(self.discountMoney) -Number(self.exchange_amount) //exchange_amount 积分兑换的金额
                map.discountMoney=self.discountMoney
                map.vipPointRate=1
              //  map.put("retailAmount", retailAmount);
               // map.put("discountMoney", String.valueOf(exchangeMoney + Double.parseDouble(discountMoney)));

              //  map.put("vipPointRate", String.valueOf(vipPointRate));
              //  map.put("vipDiscount", String.valueOf(vipDiscount));
              //  map.put("posBackAudit", String.valueOf(posBackAudit));
                map.qty= self.QuantitySum;
                map.memo='demo生成====';
                map.type=self.type
                map.exchangedPoint='0'
                map.posBackAudit=false


                net.post(pref.getString('ip')+saveMethod,map,{},function(){
                    //start
                    progress.showFull('保存中...',true)
                },function(e){
                    //success

                    progress.dismiss();
                    self.savetitle ='新增'
                },function(e){
                    //exception

                },function(){
                    //compelete

                });





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
    .iconfont {
        font-family:iconfont;  /*必须写哦！！ */
    }
    .bar-ic{
    /*  padding-top: 14px; */
      font-size: 100px;
      color: #0085ee;
  }
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
      line-height: 70px;

  }
    .cell:active{ /*按下的样式*/
        background-color: #0085ee;
    }
  .input {
      border-width: 1px;
      margin-bottom: 10px;
      height: 100px;
      width: 500px;
      background-color: #FFF;
  }
  .dialoginput{
      border-bottom-width: 1px;
      height: 50px;
      width: 300px;


  }
  .input1 {
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
      height: 230px;width: 750px; position: fixed;bottom: 0;left: 0;right: 0;
      background-color: #1EA5FC;
  }
  .text{
      width:100px;
     direction: ltr;
  }
</style>
