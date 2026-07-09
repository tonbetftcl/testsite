firebase.initializeApp({
    apiKey: "AIzaSyCG1FHpgPg3xC9IHZ0SzaPn0Ngxk8IbwS4",
    authDomain: "tonbetftcl.firebaseapp.com",
    databaseURL: "https://tonbetftcl-default-rtdb.firebaseio.com",
    projectId: "tonbetftcl",
    storageBucket: "tonbetftcl.firebasestorage.app",
    messagingSenderId: "683608892991",
    appId: "1:683608892991:web:bd70872ad2f130b8a3ba8a"
});
// Делаем db глобальной переменной
window.db = firebase.database();
