import "./Loading.css";

export function Loading() {
    return (
        <div className="loading-container">
            <div className="spinner" />
            <span>Loading...</span>
        </div>
    );
}
