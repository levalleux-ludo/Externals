define("CustomerFeedback",[window,"EventUtils","StyleUtils"],function(m,e,d,n){return function(h){var a=document.getElementById("dra-html"),b=document.createElement("iframe");b.id="cookieDropper";for(var k=nut(".item"),f=[],g=0;g<k.length;++g){var l=k[g].getAttribute("data-ph-category");if(!("string"===typeof l||l instanceof String)||0===l.length)return showFallback(Error("cf:item-with-no-hc"));f=f.concat(l.split(","))}k=function(){d.existsClass("trashed",a.className)?(b.contentWindow.postMessage("RESTORE,"+
f.join(","),h),a.className=d.removeClass("trashed",a.className),e.trigger("restored",!0)):(b.contentWindow.postMessage("TRASH,"+f.join(","),h),a.className=d.addClass("trashed",a.className),e.trigger("trashed",!0))};window.addEventListener("message",function(c){if(!d.existsClass("trashed",a.className)&&0===h.toUpperCase().indexOf(c.origin.toUpperCase())){if(!("string"===typeof c.data||c.data instanceof String))return showFallback(Error("cf:no-message"));if(0!==c.data.length){c=c.data.split(",");for(var b=
0;b<c.length;++b)if(-1<f.indexOf(c[b])){a.className=d.addClass("trashed",a.className);e.trigger("pretrashed",!0);break}}a.className=d.removeClass("hasNotCheckedCookie",a.className);e.trigger("dra-cookies-checked",!0)}},!1);(g=nut("#privacy_with_customer_feedback .trash")[0])&&e.attach({element:g,event:"click",callback:k});b.src=h+"/cookieDropper.html";a.appendChild(b)}});