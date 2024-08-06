<?php
        $targetUrl = "https://www.google.com/";
        $proxyServer = "http://";
        $proxyUserPwd = "user:psswd";
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $targetUrl);
        curl_setopt($ch, CURLOPT_HTTPPROXYTUNNEL, false);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_PROXYTYPE, 0); //http
        // curl_setopt($ch, CURLOPT_PROXYTYPE, 5); //sock5
        curl_setopt($ch, CURLOPT_PROXY, $proxyServer);
        curl_setopt($ch, CURLOPT_PROXYAUTH, CURLAUTH_BASIC);
        curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727;)");
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 3);
        curl_setopt($ch, CURLOPT_TIMEOUT, 5);
        curl_setopt($ch, CURLOPT_HEADER, true);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_PROXYUSERPWD, $proxyUserPwd);
        $result = curl_exec($ch);
        $err = curl_error($ch);
        curl_close($ch);
        var_dump($err);
        var_dump($result);
