let loginEle = document.getElementById('login');
let loginPostEle = document.getElementById('login-post');
let usernameEle = document.getElementById('username');
let passwordEle = document.getElementById('password');
loginEle.addEventListener('click', () => {
    fetch(`/api/login?username=${usernameEle.value}&password=${passwordEle.value}`)
        .then(res => res.json())
        .then(data => console.log(data))
})
loginPostEle.addEventListener('click', () => {
    fetch('/api/login_post', {
        method: 'post',
        body: JSON.stringify({
            username: usernameEle.value,
            password: passwordEle.value,
        }),
        headers: {
            'Content-Type': 'application/json;charset=utf8'
        },
    }).then(res => res.json()).then(data => console.log(data))
})