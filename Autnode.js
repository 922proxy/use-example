#!/usr/bin/env node
	require('request-promise')({
		url: 'https://ipinfo.io',
		proxy: 'http://???-zone-custom:????@ ip.proxys5.net:6500 ',
		})
	.then(function(data){ console.log(data); },
		function(err){ console.error(err); });