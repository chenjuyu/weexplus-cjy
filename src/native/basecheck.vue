<template>
    <div class="demo"  ref="cjy" :style="cityExtendStyle" v-if="displayflag">
    
    <head :autoback="false" @backClick="back" rightButton=""></head>
        <div>
            <wxc-searchbar ref="wxc-searchbar"
                           @wxcSearchbarCancelClicked="wxcSearchbarCancelClicked"
                           @wxcSearchbarInputReturned="wxcSearchbarInputReturned"
                           @wxcSearchbarInputOnInput="wxcSearchbarInputOnInput"
                           @wxcSearchbarCloseClicked="wxcSearchbarCloseClicked"
                           @wxcSearchbarInputOnFocus="wxcSearchbarInputOnFocus"
                           @wxcSearchbarInputOnBlur="wxcSearchbarInputOnBlur"></wxc-searchbar>
        </div>
    
    
     <scroller>
            <div class="margin">
                <wxc-checkbox-list :list="list"
                                   @wxcCheckBoxListChecked="wxcCheckBoxListChecked"></wxc-checkbox-list>
                <text class="checked-text">选中项 {{checkedList.toString()}}</text>
            </div>

        <wxc-button text="确定"
                    @wxcButtonClicked="wxcButtonClicked"></wxc-button>
     </scroller>
    </div>

</template>

<script>
    const  pref=weex.requireModule('pref');
    import { WxcCheckbox,WxcCheckboxList,WxcButton,WxcSearchbar,Utils  } from 'weex-ui'
    export default {
        components:{WxcCheckbox, WxcCheckboxList,WxcButton,WxcSearchbar},
       data() {
        return {
            name: "basecheck",
            list: [
               { title: '选项1', value: 1 },
                { title: '选项2', value: 2, checked: true },
                { title: '选项3', value: 3 },
                { title: '选项4', value: 4 }
            ],
            checkedList: []
        }
       }, props: {
            displayflag:{
                default:false
            },
            animationType: {
                type: String,
                default: 'push'
            }
        },
        created(){




        },

        computed: {
            cityExtendStyle () {
                return Utils.uiStyle.pageTransitionAnimationStyle(this.animationType)
            }

        },
        methods: {
        back(){
                 this.show(false);
             },
             setValue () {
                 this.$refs['wxc-searchbar'].setValue('点击了手动设置输入框内容的开关');
             },
             wxcSearchbarInputOnFocus () {
                 modal.toast({ 'message': 'onfocus', 'duration': 1 });
             },
             wxcSearchbarInputOnBlur () {
                 modal.toast({ 'message': 'onbulr', 'duration': 1 });
             },
             wxcSearchbarCloseClicked () {
                 modal.toast({ 'message': 'close.click', 'duration': 1 });
             },
             wxcSearchbarInputOnInput (e) {
                 this.value = e.value;
             },
             wxcSearchbarCancelClicked () {
                 modal.toast({ 'message': 'cancel.click', 'duration': 1 });
             },
             wxcSearchbarInputDisabledClicked () {
                 modal.toast({ 'message': 'input.onclick', 'duration': 1 });
             },
             wxcSearchbarDepChooseClicked () {
                 modal.toast({ 'message': 'dep.choose.click', 'duration': 1 });
             },
            wxcCheckBoxListChecked (e){
                this.checkedList = e.checkedList;
            }, wxcButtonClicked (e) {
                //this.alert(this.checkedList)

               this.show(false);
                this.displayflag=false
                this.$emit('choice', { item: this.checkedList.toString() });
               // this.DestroyIncomeStatistics = false; //强制刷新子组件 标识
                this.checkedList.splice(0,this.checkedList.length)
                this.list.splice(0,this.list.length)
                console.log(e)
            }, show(status = true, callback = null) {
                const ref = this.$refs.cjy
                if (this.animationType === 'push') {
                    Utils.animation.pageTransitionAnimation(ref, `translateX(${status ? -750 : 750}px)`, status, callback)
                } else if (this.animationType === 'model') {
                    Utils.animation.pageTransitionAnimation(ref, `translateY(${status ? -Utils.env.getScreenHeight() : Utils.env.getScreenHeight()}px)`, status, callback)
                }
            },showpost(e){
                this.displayflag=true
                var parma={};
                var url='/select.do?getCustomer'
                parma.currPage=1;
                // self.alert('运行到这里')
                const net = weex.requireModule('net');
                net.post(pref.getString('ip')+url,{"currPage":"1"},{},function () {
                    //start

                }, (e)=>{
                    //this.alert(e.obj)
                    //success
                    //  debugger
                    this.list.splice(0,this.list.length)
                    // this.$refs.cjy.checkedList.splice(0,this.$refs.cjy.checkedList.length)


                    console.log("res对象:"+e.res);
                    console.log("res对象里的obj对象中的username:"+e.res.obj);
                    var array=e.res.obj
                    for(var i=0;i<array.length;i++){
                        var map={}
                        map.title=array[i].Customer
                        map.value=array[i].CustomerID
                        map.checked=false
                        this.list.push(map)
                    }  },function(e){
                    //compelete

                },function(e){
                    //exception
                    //  this.alert("返回数据失败")
                });
            }
        }
    }
</script>

<style scoped>

    .demo {
        position: fixed;
        width: 750px;
        background-color: #F2F3F4;
    }

</style>
