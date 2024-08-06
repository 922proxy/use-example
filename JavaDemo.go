

package demo;

import okhttp3.Credentials;
import okhttp3.OkHttpClient;
import okhttp3.Request;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.PasswordAuthentication;
import java.net.Proxy;

/**
 * compile 'com.squareup.okhttp3:okhttp:3.10.0'
 */
class AutProxyJava {
	public static void main(String[] args) throws IOException {
		testWithOkHttp();

		testSocks5WithOkHttp();
	}

	public static void testWithOkHttp() throws IOException {
		String url = "https://api.ipify.org?format=json";
		Proxy proxy = new Proxy(Proxy.Type.HTTP, new InetSocketAddress("ip.proxys5.net", 6500));
		OkHttpClient client = new OkHttpClient().newBuilder().proxy(proxy).proxyAuthenticator((route, response) -> {
			String credential = Credentials.basic("username-zone-custom", password);
				return response.request().newBuilder()
			.header("Proxy-Authorization", credential).build();
		}).build();


		Request request = new Request.Builder().url(url).build();
		okhttp3.Response response = client.newCall(request).execute();
		String responseString = response.body().string();
		System.out.println(responseString);
	}

	public static void testSocks5WithOkHttp() throws IOException {
		String url = "https://api.ipify.org?format=json";
		Proxy proxy = new Proxy(Proxy.Type.SOCKS, new InetSocketAddress("ip.proxys5.net", 6500));
		java.net.Authenticator.setDefault(new java.net.Authenticator() {
			private PasswordAuthentication authentication =
			new PasswordAuthentication("laylay-zone-isp", "123456".toCharArray());

			@Override
			protected PasswordAuthentication getPasswordAuthentication() {
				return authentication;
			}
		});
		OkHttpClient client = new OkHttpClient().newBuilder().proxy(proxy).build();

		Request request = new Request.Builder().url(url).build();
		okhttp3.Response response = client.newCall(request).execute();
		String responseString = response.body().string();
		System.out.println(responseString);
	}
}
