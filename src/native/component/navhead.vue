<template>
    <div class="layout" :style="{ 'background-color':bgcolor,height: height +'px'}">
        <div class="demo">
            <wxc-minibar title="标题"
                         background-color="#1EA5FC"
                         text-color="#FFFFFF"
                         right-text="更多"
                         @wxcMinibarLeftButtonClicked="minibarLeftButtonClick"
                         @wxcMinibarRightButtonClicked="minibarRightButtonClick"></wxc-minibar>
        </div>
    </div>
</template>

<script>
    import { WxcMinibar } from 'weex-ui';
    const modal = weex.requireModule('modal');

    export default {
        components: { WxcMinibar },
        props:{
            height:{
                default:120
            },
            autoback: {
                default: true
            },     bgcolor: {
                default: '#1EA5FC'

            },
        },
        methods: {
            minibarLeftButtonClick () {
                if(this.autoback)
                {
                    var nav = weex.requireModule("navigator");
                    nav.back();
                    return;
                }
                this.$emit('backClick');
            },
            minibarRightButtonClick () {
                modal.toast({ 'message': 'click rightButton!', 'duration': 1 });
            },
            adjust()
            {
                if (weex.config.env.platform == 'android') {
//                    if(weex.config.env.osVersion=)
                    var p = weex.config.env.osVersion
                    p = p.replace(/\./g, '')
                    if (p.length < 3)
                        p = p + "0";
                    if (p <= '440') {
                        this.height = 108
                        this.top = 16;
                        this.titletop = 4;
                    }
                }
            }
        },     created: function () {


            this.adjust();

        },
    };
</script>
<style>
    .layout {
        background-color: #02993c;
        width: 750;
        flex-direction: row;
        align-items: center;
        justify-content: center;

    }  .demo {
           width: 750px;
           height: 180px;
           align-items: flex-start;
           padding-top: 70px;
       }
</style>