/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


var hwNameSpace = {
    initialize: function() {
            var latlng = new google.maps.LatLng(-34.397, 150.644);
            var myOptions = {
                zoom: 8,
                center: latlng,
                mapTypeId: google.maps.MapTypeId.ROADMAP,
                disableDefaultUI: true, //disable the default, allow granular control
                navigationControl: true, //enable navigation
                streetViewControl: false,
                noClear: true,
                navigationControlOptions: {
                    position: google.maps.ControlPosition.TOP_RIGHT
                },

                mapTypeControl: true,
                mapTypeControlOptions: {
                    style: google.maps.MapTypeControlStyle.DROPDOWN_MENU,
                    position: google.maps.ControlPosition.TOP,
                    mapTypeIds: [
                        google.maps.MapTypeId.ROADMAP,
                        google.maps.MapTypeId.SATELLITE
                    ]
                }
            };
            this.map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);

            document.getElementById('getValues').onclick = function() {
                console.log("current zoom level is %s", hwNameSpace.map.getZoom());
            };

    },
    markerInCenter: function() {
            this.marker = new google.maps.Marker({
                position: hwNameSpace.map.getCenter(),
                map: hwNameSpace.map,
                title: hwNameSpace.map.getCenter().toString()
            });
    }
};
